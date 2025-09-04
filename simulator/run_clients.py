import time
import managers


def main():
    print("Starting FIX Clients...")

    configManager = managers.ConfigManager("clients_config.json")
    clientManager = managers.ClientManager(configManager)

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