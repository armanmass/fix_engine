#include "quickfix/Application.h"
#include "quickfix/Message.h"
#include "quickfix/Session.h"
#include <iostream>
#include <ostream>
#include <quickfix/FixFields.h>
#include <quickfix/FixValues.h>
#include "FIXMessageOrder.hpp"


class FixApplication : public FIX::Application
{
    void fromApp(const FIX::Message& message, const FIX::SessionID& sessionID) override
    {
        const std::string& targetCompID = sessionID.getTargetCompID().getValue();
        std::cout << "Received message from client: " << targetCompID << '\n';
        std::cout << "FIX::Message: " << message.toString() << '\n';

        FIXMessageOrder order = fixMessageToOrder(message);
        // gRPC and IPC to matching_engine and database q/kdb+
    }

    void onCreate(const FIX::SessionID& sessionID) override {}
    void onLogon(const FIX::SessionID& sessionID) override {}
    void onLogout(const FIX::SessionID& sessionID) override {}
    void toAdmin(FIX::Message&  message, const FIX::SessionID& sessionID) override {}
    void toApp(FIX::Message& message, const FIX::SessionID& sessionID) override {}
    void fromAdmin(const FIX::Message &, const FIX::SessionID &) override {}
private:
    FIXMessageOrder fixMessageToOrder(const FIX::Message& message)
    {
        FIX::Symbol   fixSymbol;
        FIX::ClOrdID  fixOrderID;
        FIX::Side     fixSide;
        FIX::OrderQty fixQuantity;
        FIX::Price    fixPrice;

        message.getField(fixSymbol);
        message.getField(fixOrderID);
        message.getField(fixSide);
        message.getField(fixQuantity);
        message.getField(fixPrice);

        std::cout << "Symbol:   " << fixSymbol.getValue()   << '\n';
        std::cout << "Order ID: " << fixOrderID.getValue()  << '\n';
        std::cout << "Order ID: " << fixOrderID.getValue()  << '\n';
        std::cout << "Side:     " << fixSide.getValue()     << '\n';
        std::cout << "Quantity: " << fixQuantity.getValue() << '\n';
        std::cout << "Price:    " << fixPrice.getValue()    << '\n';

        return FIXMessageOrder 
        {
            fixSymbol.getValue(),
            static_cast<FIXMessageOrder::OrderID>(std::stoi(fixOrderID.getValue())),
            fixSide == FIX::Side_BUY ? FIXMessageOrder::Side::Buy : FIXMessageOrder::Side::Sell,
            static_cast<FIXMessageOrder::Price>(fixPrice.getValue()*10),
            static_cast<FIXMessageOrder::Quantity>(fixQuantity.getValue())
        };
    }
};
