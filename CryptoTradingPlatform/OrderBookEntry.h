#pragma once
#include <string>
enum class OrderBookType
{
    bid,
    ask,
    unknown
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
};
