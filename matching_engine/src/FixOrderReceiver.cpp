#include "FixOrderReceiver.hpp"
#include "MatchingEngine.hpp"
#include "Order.hpp"
#include <iostream>

FixOrderReceiver::FixOrderReceiver(MatchingEngine& matchingEngine)
    : matchingEngine_(matchingEngine) 
{ }

grpc::Status FixOrderReceiver::SendOrder([[maybe_unused]] grpc::ServerContext* context, const fixOrder::FIXOrder* request, fixOrder::OrderReply* reply) 
{
    OrderType orderType = OrderType::GoodTillCancel;
    OrderId orderId     = request->order_id();
    Side side           = request->side() == fixOrder::FIXOrder_Side_BUY ? Side::Buy : Side::Sell;
    Price price         = request->price();
    Quantity quantity   = request->quantity();

    auto order = std::make_shared<Order>(orderType, orderId, side, price, quantity);
    matchingEngine_.addOrder(request->instrument(), order);

    std::cout << "Received and processed order: " << orderId << " for " << request->instrument() << ".\n";

    reply->set_success(true);
    reply->set_message("Order received and processed.");
    return grpc::Status::OK;
}
