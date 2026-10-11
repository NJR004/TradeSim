#ifndef TRADER_H
#define TRADER_H

#include <string>

class Trader
{
private:
    int traderId;
    std::string name;

    double cash;
    int holdings;

public:
    Trader(int traderId,
           const std::string& name,
           double initialCash);

    int getTraderId() const;

    std::string getName() const;

    double getCash() const;

    int getHoldings() const;

    bool deductCash(double amount);

    void addCash(double amount);

    bool addHoldings(int quantity);

    bool removeHoldings(int quantity);

    void display() const;
};

#endif