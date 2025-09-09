#pragma once

#include "OrderTypes.hpp"
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

private:
    std::unordered_map<std::string, std::unique_ptr<OrderBook>> orderBooks_;
};
