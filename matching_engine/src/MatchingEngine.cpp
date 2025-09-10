#include "MatchingEngine.hpp"
#include "OrderBook.hpp"
#include "OrderTypes.hpp"
#include "k.h"
#include <chrono>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <format>

MatchingEngine::MatchingEngine()
{
    char hostname[] = "localhost";
    I port = 9788;
    char credentials[] = "";
    kdb_handle_ = khpu(hostname, port, credentials);
    if (kdb_handle_ < 0)
        throw std::runtime_error(std::format("MatchingEngine failed to connect to kdb+ on port {}.\n", port));
    if (kdb_handle_ == 0)
        throw std::runtime_error(std::format("MatchingEngine failed to verify credentials: {}\n", credentials));
    std::cout << std::format("Successfully connected to kdb+ tradesdb with handle {} on port {}.\n", kdb_handle_, port);
}

MatchingEngine::~MatchingEngine()
{
    if (kdb_handle_ > 0)
    {
        kclose(kdb_handle_);
        std::cout << std::format("Successfully closed kdb+ connect handle {}.", kdb_handle_);
    }
}

void MatchingEngine::addOrder(const std::string& instrument, OrderPointer order) 
{
    auto [it, _] = orderBooks_.try_emplace(instrument, std::make_unique<OrderBook>(std::string{instrument}));
    Trades trades = it->second->addOrder(order);
    sendToKDB(instrument, trades);
}

void MatchingEngine::sendToKDB(const std::string& instrument, const Trades& trades)
{
    if (trades.empty()) return;
    if (kdb_handle_ < 1)
    {
        std::cerr << "kdb+ Handle Failure. Trades not sent.\n";
        return;
    }


    using namespace std::chrono;
    static const auto kdbEpochOffset{seconds(946684800)};
    const auto now = system_clock::now();
    const auto kdbNow = now.time_since_epoch() - kdbEpochOffset;
    const auto kdbNowNanos = duration_cast<nanoseconds>(kdbNow).count();

    // J is long long defined in k.h which is j=long in kdb+ 8byte int
    const J numTrades = trades.size();
        K timestamps = ktn(KP, numTrades);
    K symbols    = ktn(KS, numTrades);
    K prices     = ktn(KF, numTrades);
    K quantities = ktn(KI, numTrades);

    for (J i{}; i<numTrades; ++i)
    {
        const auto& trade = trades[i];
        Price price = trade.getAskTrade().price_;
        Quantity quantity = trade.getAskTrade().quantity_;

        kJ(timestamps)[i] = kdbNowNanos;
        kS(symbols)[i]    = ss((S)instrument.c_str());
        kF(prices)[i]     = static_cast<double>(price) / 10000.0;
        kI(quantities)[i] = static_cast<int>(quantity);
    }

    // create column names
    // wants char* (not const) + ss (string to symbol)
    K colNames = ktn(KS, 4);
    char time[] = "time";
    char sym[] = "sym";
    char price[] = "price";
    char quantity[] = "quantity";
    kS(colNames)[0] = ss(time);
    kS(colNames)[1] = ss(sym); 
    kS(colNames)[2] = ss(price);
    kS(colNames)[3] = ss(quantity);

    // create column data
    K colData = ktn(0, 4);
    kK(colData)[0] = timestamps;
    kK(colData)[1] = symbols;
    kK(colData)[2] = prices;
    kK(colData)[3] = quantities;

    // join column name and column data
    K dict = ktn(0,2);
    kK(dict)[0] = colNames;
    kK(dict)[1] = colData;
    dict->t = XD;

    // convert from dict to table
    K tradeTable = xT(dict);

    char insert[] = "insert";
    char tableName[] = "tradesdb";
    K result = k(kdb_handle_, insert, ks(tableName), tradeTable, (K)0);

    if (result == nullptr)
    {
        std::cerr << "Error sending trades to kdb+.\n";
    }
    else
    {
        if (result->t == -128)
            std::cerr << "kdb+ error processing trades: " << result->s << "\n";
        r0(result);
    }
}
