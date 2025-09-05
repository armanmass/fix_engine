#pragma once

#include <cstdint>

enum class Side { Buy, Sell };

using OrderID  = uint32_t;
using Price    = uint32_t;
using Quantity = uint32_t;

struct Order 
{
    OrderID orderID;
    Side side;
    Price price;
    Quantity quantity;
};
