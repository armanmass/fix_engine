#include <quickfix/Application.h>

#include <quickfix/Exceptions.h>
#include <quickfix/Session.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/SocketAcceptor.h>

#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>

#include <iostream>
#include <filesystem>
#include "FixApplication.hpp"

int main()
{
    try
    {
        std::filesystem::path exeDir = std::filesystem::canonical(std::filesystem::path("/proc/self/exe")).parent_path();
        std::filesystem::current_path(exeDir);
        std::filesystem::path serverConfig = exeDir / "server.cfg";

std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
std::cout << "Config file path: " << serverConfig << std::endl;
std::cout << "FIXT11.xml exists in CWD: " << std::filesystem::exists("FIXT11.xml") << std::endl;
std::cout << "FIX50SP2.xml exists in CWD: " << std::filesystem::exists("FIX50SP2.xml") << std::endl;

        FixApplication application;

        FIX::SessionSettings settings{ serverConfig.string() };

        FIX::FileStoreFactory storeFactory{ settings };
        FIX::FileLogFactory logFactory{ settings };

        FIX::SocketAcceptor sockAcceptor
        {
            application,
            storeFactory,
            settings,
            logFactory
        };

        sockAcceptor.start();
std::cout << "Starting ...\n";
        // while (true)? 
        sockAcceptor.stop();

    }
    catch(FIX::ConfigError& e)
    {

        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}