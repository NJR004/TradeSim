#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "OrderBook.h"
#include "Trade.h"

#include <string>
#include <vector>

class FileManager
{
public:
    static bool saveTrades(
        const std::string& filename,
        const std::vector<Trade>& trades
    );

    static bool saveOrders(
        const std::string& filename,
        const OrderBook& orderBook
    );
};

#endif