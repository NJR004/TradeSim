#ifndef PORTFOLIO_H
#define PORTFOLIO_H

class Portfolio
{
private:
    int traderId;

    double cash;
    int holdings;

    double totalBuyValue;
    double totalSellValue;

public:
    Portfolio(
        int traderId,
        double initialCash,
        int initialHoldings = 0
    );

    int getTraderId() const;

    double getCash() const;
    int getHoldings() const;

    double getTotalBuyValue() const;
    double getTotalSellValue() const;

    bool processBuy(
        double price,
        int quantity
    );

    bool processSell(
        double price,
        int quantity
    );

    double calculatePnL() const;

    void display() const;
};

#endif