#include "../include/FileManager.h"

#include <fstream>

bool FileManager::saveTrades(
    const std::string& filename,
    const std::vector<Trade>& trades
)
{
    std::ofstream file(filename);

    if (!file.is_open())
        return false;

    file << "TradeID,BuyOrderID,SellOrderID,Price,Quantity,Timestamp\n";

    for (const auto& trade : trades)
    {
        file
            << trade.getTradeId() << ","
            << trade.getBuyOrderId() << ","
            << trade.getSellOrderId() << ","
            << trade.getPrice() << ","
            << trade.getQuantity() << ","
            << trade.getTimestamp()
            << "\n";
    }

    file.close();

    return true;
}

bool FileManager::saveOrders(
    const std::string& filename,
    const OrderBook& orderBook
)
{
    std::ofstream file(filename);

    if (!file.is_open())
        return false;

    file << "OrderID,TraderID,Side,Price,Quantity,Remaining,Timestamp\n";

    for (const auto& order : orderBook.getBuyOrders())
    {
        file
            << order->getOrderId() << ","
            << order->getTraderId() << ","
            << "BUY" << ","
            << order->getPrice() << ","
            << order->getQuantity() << ","
            << order->getRemainingQuantity() << ","
            << order->getTimestamp()
            << "\n";
    }

    for (const auto& order : orderBook.getSellOrders())
    {
        file
            << order->getOrderId() << ","
            << order->getTraderId() << ","
            << "SELL" << ","
            << order->getPrice() << ","
            << order->getQuantity() << ","
            << order->getRemainingQuantity() << ","
            << order->getTimestamp()
            << "\n";
    }

    file.close();

    return true;
}