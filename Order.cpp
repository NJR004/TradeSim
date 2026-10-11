#include "../include/Order.h"

#include <iostream>
#include <stdexcept>

// ========================================
// STATIC ORDER ID COUNTER
// ========================================

int Order::nextOrderId = 1000;


// ========================================
// EXISTING CONSTRUCTOR
// ========================================

Order::Order(
    int orderId,
    int traderId,
    OrderSide side,
    double price,
    int quantity,
    long long timestamp
)
{
    if (price <= 0)
    {
        throw std::invalid_argument(
            "Price must be greater than zero."
        );
    }

    if (quantity <= 0)
    {
        throw std::invalid_argument(
            "Quantity must be greater than zero."
        );
    }

    this->orderId = orderId;

    this->traderId = traderId;

    this->side = side;

    this->price = price;

    this->quantity = quantity;

    this->remainingQuantity = quantity;

    this->timestamp = timestamp;

    this->status = OrderStatus::PENDING;
}


// ========================================
// NEW AUTOMATIC-ID CONSTRUCTOR
// ========================================

Order::Order(
    int traderId,
    OrderSide side,
    double price,
    int quantity,
    long long timestamp
)
{
    if (price <= 0)
    {
        throw std::invalid_argument(
            "Price must be greater than zero."
        );
    }

    if (quantity <= 0)
    {
        throw std::invalid_argument(
            "Quantity must be greater than zero."
        );
    }

    // Automatically generate unique Order ID
    this->orderId = generateOrderId();

    this->traderId = traderId;

    this->side = side;

    this->price = price;

    this->quantity = quantity;

    this->remainingQuantity = quantity;

    this->timestamp = timestamp;

    this->status = OrderStatus::PENDING;
}


// ========================================
// GENERATE ORDER ID
// ========================================

int Order::generateOrderId()
{
    return nextOrderId++;
}


// ========================================
// GETTERS
// ========================================

int Order::getOrderId() const
{
    return orderId;
}

int Order::getTraderId() const
{
    return traderId;
}

OrderSide Order::getSide() const
{
    return side;
}

double Order::getPrice() const
{
    return price;
}

int Order::getQuantity() const
{
    return quantity;
}

int Order::getRemainingQuantity() const
{
    return remainingQuantity;
}

long long Order::getTimestamp() const
{
    return timestamp;
}

OrderStatus Order::getStatus() const
{
    return status;
}


// ========================================
// FILL ORDER
// ========================================

void Order::fill(int quantityToFill)
{
    if (quantityToFill <= 0)
    {
        throw std::invalid_argument(
            "Fill quantity must be greater than zero."
        );
    }

    if (quantityToFill > remainingQuantity)
    {
        throw std::invalid_argument(
            "Fill quantity exceeds remaining quantity."
        );
    }

    remainingQuantity -= quantityToFill;

    if (remainingQuantity == 0)
    {
        status = OrderStatus::FILLED;
    }
    else
    {
        status = OrderStatus::PARTIALLY_FILLED;
    }
}


// ========================================
// CANCEL ORDER
// ========================================

void Order::cancel()
{
    if (status == OrderStatus::FILLED)
    {
        throw std::runtime_error(
            "Cannot cancel a filled order."
        );
    }

    if (status == OrderStatus::CANCELLED)
    {
        throw std::runtime_error(
            "Order is already cancelled."
        );
    }

    status = OrderStatus::CANCELLED;
}


// ========================================
// CHECK ACTIVE STATUS
// ========================================

bool Order::isActive() const
{
    return (
        status == OrderStatus::PENDING ||
        status == OrderStatus::PARTIALLY_FILLED
    );
}


// ========================================
// DISPLAY ORDER
// ========================================

void Order::display() const
{
    std::cout
        << "Order ID: "
        << orderId
        << "\n";

    std::cout
        << "Trader ID: "
        << traderId
        << "\n";

    std::cout
        << "Side: ";

    if (side == OrderSide::BUY)
    {
        std::cout << "BUY";
    }
    else
    {
        std::cout << "SELL";
    }

    std::cout
        << "\n";

    std::cout
        << "Price: "
        << price
        << "\n";

    std::cout
        << "Quantity: "
        << quantity
        << "\n";

    std::cout
        << "Remaining: "
        << remainingQuantity
        << "\n";

    std::cout
        << "Timestamp: "
        << timestamp
        << "\n";

    std::cout
        << "Status: ";

    switch (status)
    {
        case OrderStatus::PENDING:
            std::cout << "PENDING";
            break;

        case OrderStatus::PARTIALLY_FILLED:
            std::cout << "PARTIALLY FILLED";
            break;

        case OrderStatus::FILLED:
            std::cout << "FILLED";
            break;

        case OrderStatus::CANCELLED:
            std::cout << "CANCELLED";
            break;
    }

    std::cout << "\n";

    std::cout
        << "------------------------------------\n";
}