#include "../include/Portfolio.h"

#include <iostream>
#include <stdexcept>

Portfolio::Portfolio(
    int traderId,
    double initialCash,
    int initialHoldings
)
{
    if (initialCash < 0)
    {
        throw std::invalid_argument(
            "Initial cash cannot be negative."
        );
    }

    if (initialHoldings < 0)
    {
        throw std::invalid_argument(
            "Initial holdings cannot be negative."
        );
    }

    this->traderId = traderId;
    this->cash = initialCash;
    this->holdings = initialHoldings;

    this->totalBuyValue = 0;
    this->totalSellValue = 0;
}

int Portfolio::getTraderId() const
{
    return traderId;
}

double Portfolio::getCash() const
{
    return cash;
}

int Portfolio::getHoldings() const
{
    return holdings;
}

double Portfolio::getTotalBuyValue() const
{
    return totalBuyValue;
}

double Portfolio::getTotalSellValue() const
{
    return totalSellValue;
}

bool Portfolio::processBuy(
    double price,
    int quantity
)
{
    if (price <= 0 || quantity <= 0)
    {
        return false;
    }

    double value = price * quantity;

    if (cash < value)
    {
        return false;
    }

    cash -= value;

    holdings += quantity;

    totalBuyValue += value;

    return true;
}

bool Portfolio::processSell(
    double price,
    int quantity
)
{
    if (price <= 0 || quantity <= 0)
    {
        return false;
    }

    if (holdings < quantity)
    {
        return false;
    }

    double value = price * quantity;

    holdings -= quantity;

    cash += value;

    totalSellValue += value;

    return true;
}

double Portfolio::calculatePnL() const
{
    /*
     * This is realized cash-flow P&L:
     *
     * Total Sell Value - Total Buy Value
     *
     * Unrealized value of currently held shares
     * is not included.
     */

    return totalSellValue - totalBuyValue;
}

void Portfolio::display() const
{
    std::cout << "\n========== PORTFOLIO ==========\n";

    std::cout << "Trader ID       : "
              << traderId << "\n";

    std::cout << "Cash            : "
              << cash << "\n";

    std::cout << "Holdings        : "
              << holdings << "\n";

    std::cout << "Total Buy Value : "
              << totalBuyValue << "\n";

    std::cout << "Total Sell Value: "
              << totalSellValue << "\n";

    std::cout << "P&L             : "
              << calculatePnL() << "\n";

    std::cout << "===============================\n";
}