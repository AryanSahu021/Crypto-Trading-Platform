#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double _price,
    double _amount,
    std::string _timestamp, 
    std::string _product, 
    OrderBookType _type, 
    std::string _username)
    : price(_price),
    amount(_amount),
    timestamp(_timestamp),
    product(_product),
    type(_type),
    username(_username)
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

bool OrderBookEntry::compareByTimestmp(OrderBookEntry& e1, OrderBookEntry& e2) {
    return e1.timestamp < e2.timestamp;
}
bool OrderBookEntry::compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2) {
    return e1.price < e2.price;
}
bool OrderBookEntry::compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2) {
    return e1.price > e2.price;
}