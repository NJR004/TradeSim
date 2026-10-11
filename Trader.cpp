#include "../include/Trader.h"

#include <iostream>
#include <stdexcept>

Trader::Trader(int traderId,
               const std::string& name,
               double initialCash)
{
    if (initialCash < 0)
        throw std::invalid_argument("Initial cash cannot be negative.");

    this->traderId = traderId;
    this->name = name;
    this->cash = initialCash;
    this->holdings = 0;
}

int Trader::getTraderId() const
{
    return traderId;
}

std::string Trader::getName() const
{
    return name;
}

double Trader::getCash() const
{
    return cash;
}

int Trader::getHoldings() const
{
    return holdings;
}

bool Trader::deductCash(double amount)
{
    if (amount <= 0)
        return false;

    if (cash < amount)
        return false;

    cash -= amount;
    return true;
}

void Trader::addCash(double amount)
{
    if (amount > 0)
        cash += amount;
}

bool Trader::addHoldings(int quantity)
{
    if (quantity <= 0)
        return false;

    holdings += quantity;
    return true;
}

bool Trader::removeHoldings(int quantity)
{
    if (quantity <= 0 || holdings < quantity)
        return false;

    holdings -= quantity;
    return true;
}

void Trader::display() const
{
    std::cout << "\n-----------------------------\n";
    std::cout << "Trader ID : " << traderId << "\n";
    std::cout << "Name      : " << name << "\n";
    std::cout << "Cash      : " << cash << "\n";
    std::cout << "Holdings  : " << holdings << "\n";
    std::cout << "-----------------------------\n";
}