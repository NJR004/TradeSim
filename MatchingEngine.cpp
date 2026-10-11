#include "../include/MatchingEngine.h"

#include <algorithm>
#include <iostream>

MatchingEngine::MatchingEngine(
    OrderBook& orderBook
)
    : orderBook(orderBook),
      nextTradeId(1),
      tradeTimestamp(1)
{
}

void MatchingEngine::registerPortfolio(
    Portfolio& portfolio
)
{
    portfolios.push_back(&portfolio);
}

Portfolio* MatchingEngine::findPortfolio(
    int traderId
)
{
    for (Portfolio* portfolio : portfolios)
    {
        if (portfolio != nullptr &&
            portfolio->getTraderId() == traderId)
        {
            return portfolio;
        }
    }

    return nullptr;
}

void MatchingEngine::matchOrders()
{
    while (true)
    {
        auto buyOrder = orderBook.getBestBuy();

        auto sellOrder = orderBook.getBestSell();

        if (!buyOrder || !sellOrder)
        {
            break;
        }

        if (!buyOrder->isActive() ||
            !sellOrder->isActive())
        {
            orderBook.removeCompletedOrders();

            continue;
        }

        /*
         * A trade can happen only when:
         *
         * Best BUY >= Best SELL
         */

        if (buyOrder->getPrice() <
            sellOrder->getPrice())
        {
            break;
        }

        int executionQuantity =
            std::min(
                buyOrder->getRemainingQuantity(),
                sellOrder->getRemainingQuantity()
            );

        /*
         * Execution price:
         * use the SELL order price.
         */

        double executionPrice =
            sellOrder->getPrice();

        double transactionValue =
            executionPrice * executionQuantity;

        /*
         * Find buyer and seller portfolios.
         */

        Portfolio* buyerPortfolio =
            findPortfolio(
                buyOrder->getTraderId()
            );

        Portfolio* sellerPortfolio =
            findPortfolio(
                sellOrder->getTraderId()
            );

        /*
         * Both portfolios must exist.
         */

        if (buyerPortfolio == nullptr)
        {
            std::cout
                << "\nERROR: Buyer portfolio not found.\n";

            break;
        }

        if (sellerPortfolio == nullptr)
        {
            std::cout
                << "\nERROR: Seller portfolio not found.\n";

            break;
        }

        /*
         * Check financial resources BEFORE
         * modifying either portfolio.
         */

        if (buyerPortfolio->getCash() <
            transactionValue)
        {
            std::cout
                << "\nTrade rejected: buyer has insufficient cash.\n";

            break;
        }

        if (sellerPortfolio->getHoldings() <
            executionQuantity)
        {
            std::cout
                << "\nTrade rejected: seller has insufficient holdings.\n";

            break;
        }

        /*
         * Update buyer portfolio.
         */

        bool buyProcessed =
            buyerPortfolio->processBuy(
                executionPrice,
                executionQuantity
            );

        /*
         * Update seller portfolio.
         */

        bool sellProcessed =
            sellerPortfolio->processSell(
                executionPrice,
                executionQuantity
            );

        /*
         * Only create the trade if both
         * portfolio operations succeeded.
         */

        if (!buyProcessed || !sellProcessed)
        {
            std::cout
                << "\nTrade rejected: portfolio update failed.\n";

            break;
        }

        /*
         * Create trade record.
         */

        Trade trade(
            nextTradeId++,
            buyOrder->getOrderId(),
            sellOrder->getOrderId(),
            executionPrice,
            executionQuantity,
            tradeTimestamp++
        );

        trades.push_back(trade);

        /*
         * Update order quantities/status.
         */

        buyOrder->fill(executionQuantity);

        sellOrder->fill(executionQuantity);

        std::cout << "\nTrade Executed!\n";

        trade.display();

        /*
         * Remove completely filled orders.
         */

        orderBook.removeCompletedOrders();
    }
}

const std::vector<Trade>&
MatchingEngine::getTrades() const
{
    return trades;
}

void MatchingEngine::displayTrades() const
{
    std::cout
        << "\n========== ALL TRADES ==========\n";

    if (trades.empty())
    {
        std::cout
            << "No trades executed.\n";

        return;
    }

    for (const auto& trade : trades)
    {
        trade.display();
    }
}