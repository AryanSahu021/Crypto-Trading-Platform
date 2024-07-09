#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _type)
    : price(_price),
    amount(_amount),
    timestamp(_timestamp),
    product(_product),
    type(_type)
{
}

OrderBookType OrderBookEntry::stringToOrderBookType(const std::string& s) {
    if (s == "ask") {
        return OrderBookType::ask;
    }
    if (s == "bid") {
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
}