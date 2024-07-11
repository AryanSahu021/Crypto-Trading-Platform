#pragma once
#include <string>
enum class OrderBookType
{
    bid,
    ask,
    unknown,
    sale
};

class OrderBookEntry
{
public:
    /** Create an Order Book Entry with values as sent.
     *
     */
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType type;
    OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _type);
    static OrderBookType stringToOrderBookType(const std::string& s);
    static bool compareByTimestmp(OrderBookEntry& e1, OrderBookEntry& e2);
    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2);
    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2);
};
