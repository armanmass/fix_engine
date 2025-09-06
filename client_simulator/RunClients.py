import time
import Managers


def main():
    print("Starting FIX Clients...")

    configManager = Managers.ConfigManager("clients_config.json")
    clientManager = Managers.ClientManager(configManager)

    clientManager.startAllClients()

    try:
        while clientManager.running:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nShutting down...\n")
    finally:
        clientManager.stopAllClients()

    return 0



if __name__ == "__main__":
    main()