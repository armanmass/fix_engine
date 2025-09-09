#include "MatchingEngine.hpp"
#include "OrderBook.hpp"

MatchingEngine::MatchingEngine() = default;
MatchingEngine::~MatchingEngine() = default;

void MatchingEngine::addOrder(const std::string& instrument, OrderPointer order) 
{
    auto [it, _] = orderBooks_.try_emplace(instrument, std::make_unique<OrderBook>(std::string{instrument}));
    it->second->addOrder(order);
}
