#include "../include/OrderBook.h"

#include <algorithm>
#include <iostream>

void OrderBook::sortBuyOrders()
{
    std::sort(
        buyOrders.begin(),
        buyOrders.end(),
        [](const std::shared_ptr<Order>& a,
           const std::shared_ptr<Order>& b)
        {
            if (a->getPrice() != b->getPrice())
            {
                return a->getPrice() > b->getPrice();
            }

            return a->getTimestamp() <
                   b->getTimestamp();
        }
    );
}

void OrderBook::sortSellOrders()
{
    std::sort(
        sellOrders.begin(),
        sellOrders.end(),
        [](const std::shared_ptr<Order>& a,
           const std::shared_ptr<Order>& b)
        {
            if (a->getPrice() != b->getPrice())
            {
                return a->getPrice() < b->getPrice();
            }

            return a->getTimestamp() <
                   b->getTimestamp();
        }
    );
}

void OrderBook::addOrder(
    std::shared_ptr<Order> order
)
{
    if (!order)
        return;

    if (order->getSide() == OrderSide::BUY)
    {
        buyOrders.push_back(order);

        sortBuyOrders();
    }
    else
    {
        sellOrders.push_back(order);

        sortSellOrders();
    }
}

bool OrderBook::cancelOrder(int orderId)
{
    auto order = findOrder(orderId);

    if (!order)
        return false;

    if (!order->isActive())
        return false;

    order->cancel();

    return true;
}

std::shared_ptr<Order>
OrderBook::findOrder(int orderId)
{
    for (auto& order : buyOrders)
    {
        if (order->getOrderId() == orderId)
            return order;
    }

    for (auto& order : sellOrders)
    {
        if (order->getOrderId() == orderId)
            return order;
    }

    return nullptr;
}

std::shared_ptr<Order>
OrderBook::getBestBuy()
{
    if (buyOrders.empty())
        return nullptr;

    return buyOrders.front();
}

std::shared_ptr<Order>
OrderBook::getBestSell()
{
    if (sellOrders.empty())
        return nullptr;

    return sellOrders.front();
}

void OrderBook::removeCompletedOrders()
{
    buyOrders.erase(
        std::remove_if(
            buyOrders.begin(),
            buyOrders.end(),
            [](const std::shared_ptr<Order>& order)
            {
                return !order->isActive();
            }
        ),
        buyOrders.end()
    );

    sellOrders.erase(
        std::remove_if(
            sellOrders.begin(),
            sellOrders.end(),
            [](const std::shared_ptr<Order>& order)
            {
                return !order->isActive();
            }
        ),
        sellOrders.end()
    );
}

const std::vector<std::shared_ptr<Order>>&
OrderBook::getBuyOrders() const
{
    return buyOrders;
}

const std::vector<std::shared_ptr<Order>>&
OrderBook::getSellOrders() const
{
    return sellOrders;
}

void OrderBook::displayBuyBook() const
{
    std::cout << "\n========== BUY ORDER BOOK ==========\n";

    if (buyOrders.empty())
    {
        std::cout << "No buy orders.\n";
        return;
    }

    for (const auto& order : buyOrders)
    {
        order->display();
        std::cout << "------------------------------------\n";
    }
}

void OrderBook::displaySellBook() const
{
    std::cout << "\n========== SELL ORDER BOOK ==========\n";

    if (sellOrders.empty())
    {
        std::cout << "No sell orders.\n";
        return;
    }

    for (const auto& order : sellOrders)
    {
        order->display();
        std::cout << "-------------------------------------\n";
    }
}