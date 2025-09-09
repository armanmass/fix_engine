#include "FixOrderSender.hpp"
#include <iostream>

FixOrderSender::FixOrderSender(std::shared_ptr<grpc::Channel> channel)
    : stub_(fixOrder::OrderReceiver::NewStub(channel))
{
}

bool FixOrderSender::SendOrder(const FIXMessageOrder& order)
{
    fixOrder::FIXOrder request;
    request.set_instrument(order.instrument);
    request.set_order_id(order.orderID);
    request.set_side(order.side == FIXMessageOrder::Side::Buy ? fixOrder::FIXOrder_Side_BUY : fixOrder::FIXOrder_Side_SELL);
    request.set_price(order.price);
    request.set_quantity(order.quantity);

    fixOrder::OrderReply reply;
    grpc::ClientContext context;

    grpc::Status status = stub_->SendOrder(&context, request, &reply);

    if (status.ok())
    {
        std::cout << "gRPC call SUCCESSFUL for Order ID "  << order.orderID << ": " << reply.message() << '\n';
        return true;
    }
    else
    {
        std::cout << "gRPC call FAILED for Order ID " << order.orderID << " [ec " << status.error_code() << ": " << status.error_message() << "]\n";
        return false;
    }
}
