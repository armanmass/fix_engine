#include <quickfix/Application.h>

#include <quickfix/Exceptions.h>
#include <quickfix/Session.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/SocketAcceptor.h>

#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>

#include <iostream>
#include "FixApplication.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: ./fix_engine [fileName]\n";
        return 1;
    }

    try
    {
        std::string settingsFile{ argv[1] };

        FixApplication application;

        FIX::SessionSettings settings{ settingsFile };

        FIX::FileStoreFactory storeFactory{ settings };
        FIX::FileLogFactory logFactory{ settings };

        FIX::SocketAcceptor sockAcceptor{
            application,
            storeFactory,
            settings,
            logFactory
        };

        sockAcceptor.start();
        // condition to loop on
        sockAcceptor.stop();

    }
    catch(FIX::ConfigError& e)
    {

        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}