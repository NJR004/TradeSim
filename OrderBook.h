#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "Order.h"

#include <memory>
#include <vector>

class OrderBook
{
private:
    std::vector<std::shared_ptr<Order>> buyOrders;

    std::vector<std::shared_ptr<Order>> sellOrders;

    void sortBuyOrders();

    void sortSellOrders();

public:
    void addOrder(
        std::shared_ptr<Order> order
    );

    bool cancelOrder(
        int orderId
    );

    std::shared_ptr<Order> findOrder(
        int orderId
    );

    std::shared_ptr<Order> getBestBuy();

    std::shared_ptr<Order> getBestSell();

    void removeCompletedOrders();

    const std::vector<std::shared_ptr<Order>>&
    getBuyOrders() const;

    const std::vector<std::shared_ptr<Order>>&
    getSellOrders() const;

    void displayBuyBook() const;

    void displaySellBook() const;
};

#endif