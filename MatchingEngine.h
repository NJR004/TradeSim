#ifndef MATCHING_ENGINE_H
#define MATCHING_ENGINE_H

#include "OrderBook.h"
#include "Trade.h"
#include "Portfolio.h"

#include <vector>

class MatchingEngine
{
private:
    OrderBook& orderBook;

    std::vector<Trade> trades;

    std::vector<Portfolio*> portfolios;

    int nextTradeId;

    long long tradeTimestamp;

    Portfolio* findPortfolio(int traderId);

public:
    MatchingEngine(OrderBook& orderBook);

    void registerPortfolio(Portfolio& portfolio);

    void matchOrders();

    const std::vector<Trade>& getTrades() const;

    void displayTrades() const;
};

#endif