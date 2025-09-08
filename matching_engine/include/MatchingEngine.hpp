#pragma once

#include "OrderBook.hpp"
#include <string>
#include <unordered_map>
#include <memory>

class OrderBook;

class MatchingEngine 
{
public:
    void addOrder(const std::string& instrument, OrderPointer order);

private:
    std::unordered_map<std::string, std::unique_ptr<OrderBook>> orderBooks_;
};
