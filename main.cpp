#include <iostream>
#include <memory>
#include <vector>
#include <limits>
#include <string>

#include "include/Order.h"
#include "include/Trader.h"
#include "include/Trade.h"
#include "include/Portfolio.h"
#include "include/OrderBook.h"
#include "include/MatchingEngine.h"
#include "include/FileManager.h"

// ========================================
// GLOBAL DATA
// ========================================

std::vector<std::unique_ptr<Trader>> traders;
std::vector<std::unique_ptr<Portfolio>> portfolios;

long long nextTimestamp = 1;

// ========================================
// FIND TRADER
// ========================================

Trader* findTrader(int traderId)
{
    for (auto& trader : traders)
    {
        if (trader->getTraderId() == traderId)
        {
            return trader.get();
        }
    }

    return nullptr;
}

// ========================================
// FIND PORTFOLIO
// ========================================

Portfolio* findPortfolio(int traderId)
{
    for (auto& portfolio : portfolios)
    {
        if (portfolio->getTraderId() == traderId)
        {
            return portfolio.get();
        }
    }

    return nullptr;
}

// ========================================
// CREATE TRADER
// ========================================

void createTrader(MatchingEngine& engine)
{
    int traderId;
    std::string name;
    double cash;
    int holdings;

    std::cout << "\n========== CREATE TRADER ==========\n";

    std::cout << "Enter Trader ID: ";
    std::cin >> traderId;

    if (findTrader(traderId) != nullptr)
    {
        std::cout << "Trader ID already exists.\n";
        return;
    }

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );

    std::cout << "Enter Trader Name: ";
    std::getline(std::cin, name);

    if (name.empty())
    {
        std::cout << "Trader name cannot be empty.\n";
        return;
    }

    std::cout << "Enter Initial Cash: ";
    std::cin >> cash;

    std::cout << "Enter Initial Holdings: ";
    std::cin >> holdings;

    if (cash < 0 || holdings < 0)
    {
        std::cout << "Cash and holdings cannot be negative.\n";
        return;
    }

    try
    {
        // Create trader
        traders.push_back(
            std::make_unique<Trader>(
                traderId,
                name,
                cash
            )
        );

        // Create portfolio
        portfolios.push_back(
            std::make_unique<Portfolio>(
                traderId,
                cash,
                holdings
            )
        );

        // IMPORTANT:
        // Register the portfolio with MatchingEngine
        engine.registerPortfolio(*portfolios.back());

        std::cout << "\nTrader created successfully.\n";
        std::cout << "Trader ID: " << traderId << "\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "Initial Cash: " << cash << "\n";
        std::cout << "Initial Holdings: " << holdings << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "\nError: " << e.what() << "\n";
    }
}

// ========================================
// VIEW TRADERS
// ========================================

void viewTraders()
{
    std::cout << "\n========== ALL TRADERS ==========\n";

    if (traders.empty())
    {
        std::cout << "No traders available.\n";
        return;
    }

    for (const auto& trader : traders)
    {
        trader->display();
    }
}

// ========================================
// PLACE BUY ORDER
// ========================================

void placeBuyOrder(OrderBook& orderBook)
{
    int traderId;
    double price;
    int quantity;

    std::cout << "\n========== PLACE BUY ORDER ==========\n";

    std::cout << "Enter Trader ID: ";
    std::cin >> traderId;

    Trader* trader = findTrader(traderId);
    Portfolio* portfolio = findPortfolio(traderId);

    if (trader == nullptr || portfolio == nullptr)
    {
        std::cout << "Trader not found.\n";
        return;
    }

    std::cout << "Enter Price: ";
    std::cin >> price;

    std::cout << "Enter Quantity: ";
    std::cin >> quantity;

    if (price <= 0 || quantity <= 0)
    {
        std::cout << "Price and quantity must be positive.\n";
        return;
    }

    double requiredCash = price * quantity;

    if (portfolio->getCash() < requiredCash)
    {
        std::cout << "Insufficient cash.\n";
        std::cout << "Required: " << requiredCash << "\n";
        std::cout << "Available: "
                  << portfolio->getCash()
                  << "\n";
        return;
    }

    try
    {
        // Automatic Order ID generation
        auto order = std::make_shared<Order>(
            traderId,
            OrderSide::BUY,
            price,
            quantity,
            nextTimestamp++
        );

        orderBook.addOrder(order);

        std::cout << "\nBUY order placed successfully.\n";
        order->display();
    }
    catch (const std::exception& e)
    {
        std::cout << "\nError: " << e.what() << "\n";
    }
}

// ========================================
// PLACE SELL ORDER
// ========================================

void placeSellOrder(OrderBook& orderBook)
{
    int traderId;
    double price;
    int quantity;

    std::cout << "\n========== PLACE SELL ORDER ==========\n";

    std::cout << "Enter Trader ID: ";
    std::cin >> traderId;

    Trader* trader = findTrader(traderId);
    Portfolio* portfolio = findPortfolio(traderId);

    if (trader == nullptr || portfolio == nullptr)
    {
        std::cout << "Trader not found.\n";
        return;
    }

    std::cout << "Enter Price: ";
    std::cin >> price;

    std::cout << "Enter Quantity: ";
    std::cin >> quantity;

    if (price <= 0 || quantity <= 0)
    {
        std::cout << "Price and quantity must be positive.\n";
        return;
    }

    if (portfolio->getHoldings() < quantity)
    {
        std::cout << "Insufficient holdings.\n";
        std::cout << "Required: " << quantity << "\n";
        std::cout << "Available: "
                  << portfolio->getHoldings()
                  << "\n";
        return;
    }

    try
    {
        // Automatic Order ID generation
        auto order = std::make_shared<Order>(
            traderId,
            OrderSide::SELL,
            price,
            quantity,
            nextTimestamp++
        );

        orderBook.addOrder(order);

        std::cout << "\nSELL order placed successfully.\n";
        order->display();
    }
    catch (const std::exception& e)
    {
        std::cout << "\nError: " << e.what() << "\n";
    }
}

// ========================================
// VIEW ORDER BOOK
// ========================================

void viewOrderBook(OrderBook& orderBook)
{
    std::cout << "\n========== ORDER BOOK ==========\n";

    orderBook.displayBuyBook();
    orderBook.displaySellBook();
}

// ========================================
// VIEW TRADES
// ========================================

void viewTrades(MatchingEngine& engine)
{
    std::cout << "\n========== EXECUTED TRADES ==========\n";

    engine.displayTrades();
}

// ========================================
// VIEW PORTFOLIOS
// ========================================

void viewPortfolios()
{
    std::cout << "\n========== ALL PORTFOLIOS ==========\n";

    if (portfolios.empty())
    {
        std::cout << "No portfolios available.\n";
        return;
    }

    for (const auto& portfolio : portfolios)
    {
        portfolio->display();
    }
}

// ========================================
// SAVE DATA
// ========================================

void saveData(
    OrderBook& orderBook,
    MatchingEngine& engine
)
{
    std::cout << "\n========== SAVING DATA ==========\n";

    if (FileManager::saveOrders(
            "data/orders.txt",
            orderBook))
    {
        std::cout << "Orders saved successfully.\n";
    }
    else
    {
        std::cout << "Failed to save orders.\n";
    }

    if (FileManager::saveTrades(
            "data/trades.txt",
            engine.getTrades()))
    {
        std::cout << "Trades saved successfully.\n";
    }
    else
    {
        std::cout << "Failed to save trades.\n";
    }
}

// ========================================
// DISPLAY MENU
// ========================================

void displayMenu()
{
    std::cout
        << "\n\n========================================\n";

    std::cout
        << "       TRADESIM MARKET SIMULATOR\n";

    std::cout
        << "========================================\n";

    std::cout << "1. Create Trader\n";
    std::cout << "2. View Traders\n";
    std::cout << "3. Place BUY Order\n";
    std::cout << "4. Place SELL Order\n";
    std::cout << "5. View Order Book\n";
    std::cout << "6. Match Orders\n";
    std::cout << "7. View Executed Trades\n";
    std::cout << "8. View Portfolios\n";
    std::cout << "9. Save Data\n";
    std::cout << "0. Exit\n";

    std::cout
        << "========================================\n";

    std::cout << "Enter your choice: ";
}

// ========================================
// MAIN
// ========================================

int main()
{
    std::cout
        << "========================================\n";

    std::cout
        << "       Welcome to TradeSim\n";

    std::cout
        << "========================================\n";

    // ========================================
    // CREATE CORE COMPONENTS
    // ========================================

    OrderBook orderBook;

    MatchingEngine engine(orderBook);

    // ========================================
    // MAIN MENU LOOP
    // ========================================

    bool running = true;

    while (running)
    {
        displayMenu();

        int choice;

        if (!(std::cin >> choice))
        {
            std::cout
                << "\nInvalid input. Please enter a number.\n";

            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            continue;
        }

        switch (choice)
        {
            // ========================================
            // CREATE TRADER
            // ========================================

            case 1:
            {
                createTrader(engine);
                break;
            }

            // ========================================
            // VIEW TRADERS
            // ========================================

            case 2:
            {
                viewTraders();
                break;
            }

            // ========================================
            // PLACE BUY
            // ========================================

            case 3:
            {
                placeBuyOrder(orderBook);
                break;
            }

            // ========================================
            // PLACE SELL
            // ========================================

            case 4:
            {
                placeSellOrder(orderBook);
                break;
            }

            // ========================================
            // VIEW ORDER BOOK
            // ========================================

            case 5:
            {
                viewOrderBook(orderBook);
                break;
            }

            // ========================================
            // MATCH ORDERS
            // ========================================

            case 6:
            {
                std::cout
                    << "\n========== MATCHING ORDERS ==========\n";

                engine.matchOrders();

                break;
            }

            // ========================================
            // VIEW TRADES
            // ========================================

            case 7:
            {
                viewTrades(engine);
                break;
            }

            // ========================================
            // VIEW PORTFOLIOS
            // ========================================

            case 8:
            {
                viewPortfolios();
                break;
            }

            // ========================================
            // SAVE DATA
            // ========================================

            case 9:
            {
                saveData(
                    orderBook,
                    engine
                );

                break;
            }

            // ========================================
            // EXIT
            // ========================================

            case 0:
            {
                std::cout
                    << "\nExiting TradeSim...\n";

                running = false;

                break;
            }

            // ========================================
            // INVALID CHOICE
            // ========================================

            default:
            {
                std::cout
                    << "\nInvalid choice. Please try again.\n";

                break;
            }
        }
    }

    return 0;
}