#include "../include/Trade.h"

#include <iostream>
#include <stdexcept>

Trade::Trade(int tradeId,
             int buyOrderId,
             int sellOrderId,
             double price,
             int quantity,
             long long timestamp)
{
    if (price <= 0)
        throw std::invalid_argument("Trade price must be positive.");

    if (quantity <= 0)
        throw std::invalid_argument("Trade quantity must be positive.");

    this->tradeId = tradeId;
    this->buyOrderId = buyOrderId;
    this->sellOrderId = sellOrderId;
    this->price = price;
    this->quantity = quantity;
    this->timestamp = timestamp;
}

int Trade::getTradeId() const
{
    return tradeId;
}

int Trade::getBuyOrderId() const
{
    return buyOrderId;
}

int Trade::getSellOrderId() const
{
    return sellOrderId;
}

double Trade::getPrice() const
{
    return price;
}

int Trade::getQuantity() const
{
    return quantity;
}

long long Trade::getTimestamp() const
{
    return timestamp;
}

void Trade::display() const
{
    std::cout << "\n========== TRADE ==========\n";

    std::cout << "Trade ID      : " << tradeId << "\n";
    std::cout << "Buy Order ID  : " << buyOrderId << "\n";
    std::cout << "Sell Order ID : " << sellOrderId << "\n";
    std::cout << "Price         : " << price << "\n";
    std::cout << "Quantity      : " << quantity << "\n";
    std::cout << "Timestamp     : " << timestamp << "\n";

    std::cout << "===========================\n";
}