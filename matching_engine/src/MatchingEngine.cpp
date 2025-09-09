#include "MatchingEngine.hpp"
#include "OrderBook.hpp"
#include "k.h"

MatchingEngine::MatchingEngine() = default;
MatchingEngine::~MatchingEngine() = default;

void MatchingEngine::addOrder(const std::string& instrument, OrderPointer order) 
{
    auto [it, _] = orderBooks_.try_emplace(instrument, std::make_unique<OrderBook>(std::string{instrument}));
    Trades trades = it->second->addOrder(order);
    sendToKDB(instrument, trades);
}

void MatchingEngine::sendToKDB(const std::string& instrument, const Trades& trades)
{
    // TODO: SEND TO KDB ON PORT 9878
    // need to send add to tradesdb command
    // timestamp, symbol, price, quantity
    for (const auto& trade : trades)
    {
        //timestamp = chrono + 30 years
        
    }
}
