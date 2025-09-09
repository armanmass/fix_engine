#pragma once

#include "quickfix/Application.h"
#include "quickfix/Message.h"
#include "quickfix/Session.h"
#include <iostream>
#include <ostream>
#include <quickfix/FixFields.h>
#include <quickfix/FixValues.h>
#include "FIXMessageOrder.hpp"

#include "FixOrderSender.hpp"
#include <grpcpp/grpcpp.h>
#include <memory>

class FixApplication : public FIX::Application
{
public:
    FixApplication(std::shared_ptr<grpc::Channel> channel)
        : fixOrderSender_(std::make_unique<FixOrderSender>(channel)) 
    { }

    void fromApp(const FIX::Message& message, const FIX::SessionID& sessionID) override
    {
        const std::string& targetCompID = sessionID.getTargetCompID().getValue();
        std::cout << "Received message from client: " << targetCompID << '\n';

        FIXMessageOrder order = fixMessageToOrder(message);

        if (fixOrderSender_ != nullptr)
            fixOrderSender_->SendOrder(order);
        else
            std::cout << "Failed to send order over gRPC in FixApplication.\n";
    }

    void onCreate(const FIX::SessionID&) override {}
    void onLogon(const FIX::SessionID&) override {}
    void onLogout(const FIX::SessionID&) override {}
    void toAdmin(FIX::Message&, const FIX::SessionID&) override {}
    void toApp(FIX::Message&, const FIX::SessionID&) override {}
    void fromAdmin(const FIX::Message&, const FIX::SessionID&) override {}
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

    std::unique_ptr<FixOrderSender> fixOrderSender_;
};
