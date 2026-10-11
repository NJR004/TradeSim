#ifndef TRADE_H
#define TRADE_H

class Trade
{
private:
    int tradeId;

    int buyOrderId;
    int sellOrderId;

    double price;
    int quantity;

    long long timestamp;

public:
    Trade(int tradeId,
          int buyOrderId,
          int sellOrderId,
          double price,
          int quantity,
          long long timestamp);

    int getTradeId() const;

    int getBuyOrderId() const;

    int getSellOrderId() const;

    double getPrice() const;

    int getQuantity() const;

    long long getTimestamp() const;

    void display() const;
};

#endif