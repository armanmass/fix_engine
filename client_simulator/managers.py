import os
import time
import threading

import json
import textwrap
from typing import Any, List
from pathlib import Path
cwd = Path(__file__).parent.resolve()

import quickfix as fix
from client import FIXClient


class ConfigManager:
    def __init__(self, configFile: str = "clients_config.json"):
        self.configFile = cwd / configFile
        self.config = self.loadConfig()
    
    def loadConfig(self) -> dict[str, Any]:
        with open(self.configFile, 'r') as f:
            config = json.load(f)
            return config

    def getClients(self) -> List[dict[str, Any]]:
        return self.config.get("clients", [])
    
    def getDefaultSettings(self) -> dict[str, Any]:
        return self.config.get("default", {})

class ClientManager:
    def __init__(self, configManager: ConfigManager):
        self.configManager = configManager
        self.defaultSettings = self.configManager.getDefaultSettings()

        self.clients    = []
        self.initiators = []
        self.threads    = []
        self.running    = False
    
    def createClientConfig(self, clientConfig: dict[str, Any]) -> str:
        clientID = clientConfig["client_id"]
        senderCompID = clientConfig["sender_comp_id"]

        settings = {**self.defaultSettings, **clientConfig}

        transportDict   = f"{cwd}/../common/spec/{settings["fix_version"].replace('.','')}.xml"
        applicationDict = f"{cwd}/../common/spec/{settings["default_appl_ver_id"].replace('.','')}.xml"


        tempFolder = f"{cwd}/tmp"
        os.makedirs(tempFolder, exist_ok=True)

        configContent = textwrap.dedent(f"""
                                        [DEFAULT]
                                        FileStorePath={tempFolder}/MessageStore/store_{clientID}/
                                        FileLogPath={tempFolder}/Logs/log_{clientID}/

                                        [SESSION]
                                        BeginString={settings["fix_version"]}
                                        DefaultApplVerID={settings["default_appl_ver_id"]}
                                        SenderCompID={senderCompID}
                                        TargetCompID={settings["target_comp_id"]}
                                        ConnectionType=initiator
                                        SocketConnectHost={settings["host"]}
                                        SocketConnectPort={settings["port"]}
                                        StartTime={settings["start_time"]}
                                        EndTime={settings["end_time"]}
                                        HeartBtInt={settings["heartbeat_interval"]}
                                        TransportDataDictionary={transportDict}
                                        AppDataDictionary={applicationDict}
                                        ValidateUserDefinedFields=N
                                        ValidateFieldsOutOfOrder=N
                                        ValidateFieldsHaveValues=N
                                        ValidateIncomingMessage=Y
                                        """).strip()

        os.makedirs(f"{tempFolder}/MessageStore/store_{clientID}", exist_ok=True)
        os.makedirs(f"{tempFolder}/Logs/log_{clientID}", exist_ok=True)

        clientConfigsDir = f"{tempFolder}/ClientConfigs"
        os.makedirs(clientConfigsDir, exist_ok=True)

        configFile = f"{clientConfigsDir}/client_{clientID}.cfg"
        with open(configFile, 'w') as f:
            f.write(configContent)

        return configFile

    def startClient(self, clientConfig: dict[str, Any]) -> FIXClient | None:
        clientID = clientConfig["client_id"]

        try:
            application = FIXClient(clientID)
            configFile = self.createClientConfig(clientConfig)

            settings = fix.SessionSettings(configFile)
            storeFactory = fix.FileStoreFactory(settings)
            logFactory = fix.FileLogFactory(settings)

            initiator = fix.SocketInitiator(
                application,
                storeFactory,
                settings,
                logFactory
            )

            initiator.start()

            self.clients.append(application)
            self.initiators.append(initiator)

            print(f"Started Client {clientID} ({clientConfig["sender_comp_id"]})")
            return application


        except Exception as e:
            print(f"Error starting client {clientID}: {e}")
            return None


    def clientMessageSender(self, client: FIXClient, messageInterval: int) -> None:
        print(f"Attempting to start message sender for Client {client.clientID_}")

        maxWait = 30
        waitTime = 0

        while not client.loggedOn and waitTime < maxWait and self.running:
            time.sleep(1)
            waitTime += 1
        
        if not client.loggedOn:
            print(f"Client {client.clientID_}: Failed to establish session. (LogOn Failed)")
            return
        
        print(f"Client {client.clientID_}: Session established, sending orders. (LogOn Successful)")

        while self.running:
            try:
                client.sendNewSingleOrder()
                time.sleep(messageInterval)
            except Exception as e:
                print(f"Client {client.clientID_}: Error sending message: {e}")
                break
        
        print(f"Client {client.clientID_}: Stopping.") 
    
    def startAllClients(self) -> bool:
        clientConfigs = self.configManager.getClients()

        if not clientConfigs:
            print("Error: No client to start.")
            return False
        
        self.running = True
        messageInterval = self.defaultSettings.get("message_interval", 10)

        for clientConfig in clientConfigs:
            client = self.startClient(clientConfig)
            if client:
                print(f"Putting Client {client.clientID_} on seperate thread.")
                clientThread = threading.Thread(
                    target=self.clientMessageSender,
                    args=(client, messageInterval),
                    daemon=True
                )

                clientThread.start()
                self.threads.append(clientThread)
                time.sleep(1)
        return len(self.clients) > 0

    def stopAllClients(self) -> None:
        self.running = False

        for initiator in self.initiators:
            initiator.stop()
        
        for thread in self.threads:
            thread.join(timeout=5)
        
        print("All clients stopped.")