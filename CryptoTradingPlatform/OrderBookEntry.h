#pragma once
#include <string>
enum class OrderBookType
{
    bid,
    ask,
    unknown,
    bidsale,
    asksale
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
    std::string username;
    OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _type, std::string username = "dataset");
    static OrderBookType stringToOrderBookType(const std::string& s);
    static bool compareByTimestmp(OrderBookEntry& e1, OrderBookEntry& e2);
    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2);
    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2);
};
