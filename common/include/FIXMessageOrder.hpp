#pragma once

#include <cstdint>
#include <string>

struct FIXMessageOrder 
{
    enum class Side { Buy, Sell };

    using OrderID  = uint32_t;
    using Price    = uint32_t;
    using Quantity = uint32_t;

    std::string instrument;
    OrderID orderID;
    Side side;
    Price price;
    Quantity quantity;
};
