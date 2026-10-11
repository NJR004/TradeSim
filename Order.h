#ifndef ORDER_H
#define ORDER_H

#include <string>

enum class OrderSide
{
    BUY,
    SELL
};

enum class OrderStatus
{
    PENDING,
    PARTIALLY_FILLED,
    FILLED,
    CANCELLED
};

class Order
{
private:
    int orderId;

    int traderId;

    OrderSide side;

    double price;

    int quantity;

    int remainingQuantity;

    long long timestamp;

    OrderStatus status;

    // Used to generate unique order IDs automatically
    static int nextOrderId;

public:

    // Existing constructor
    // Useful for tests and controlled scenarios
    Order(
        int orderId,
        int traderId,
        OrderSide side,
        double price,
        int quantity,
        long long timestamp
    );

    // New constructor
    // Automatically generates the Order ID
    Order(
        int traderId,
        OrderSide side,
        double price,
        int quantity,
        long long timestamp
    );

    // Generate a new unique Order ID
    static int generateOrderId();

    // Getters
    int getOrderId() const;

    int getTraderId() const;

    OrderSide getSide() const;

    double getPrice() const;

    int getQuantity() const;

    int getRemainingQuantity() const;

    long long getTimestamp() const;

    OrderStatus getStatus() const;

    // Order operations
    void fill(int quantity);

    void cancel();

    bool isActive() const;

    // Display order
    void display() const;
};

#endif