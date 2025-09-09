#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <list>
#include <limits>

class Order;

using OrderId  = std::uint64_t;
using Price    = std::int64_t;
using Quantity = std::uint64_t;
using OrderIds = std::vector<OrderId>;
using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;

enum class OrderType { GoodTillCancel, FillAndKill, Market, GoodForDay, FillOrKill };
enum class Side { Buy, Sell };

static const Price InvalidPrice = std::numeric_limits<Price>::quiet_NaN();