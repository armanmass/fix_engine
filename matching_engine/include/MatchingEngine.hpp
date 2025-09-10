#pragma once

#include "OrderTypes.hpp"
#include "TradeInfo.hpp"
#include "k.h"
#include <string>
#include <unordered_map>
#include <memory>

class OrderBook;

class MatchingEngine 
{
public:
    MatchingEngine();
    ~MatchingEngine();
    
    MatchingEngine(const MatchingEngine&) = delete;
    MatchingEngine& operator=(const MatchingEngine&) = delete;
    MatchingEngine(MatchingEngine&&) = delete;
    MatchingEngine& operator=(MatchingEngine&&) = delete;

    void addOrder(const std::string& instrument, OrderPointer order);
    void sendToKDB(const std::string& instrument, const Trades& trades);

private:
    std::unordered_map<std::string, std::unique_ptr<OrderBook>> orderBooks_;
    I kdb_handle_;
};
