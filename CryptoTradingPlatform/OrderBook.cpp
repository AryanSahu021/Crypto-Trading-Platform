#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>
OrderBook::OrderBook(std::string filename) 
{
	orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts() 
{
	std::vector<std::string> products;
	std::map<std::string, bool> prodMap;
	for (const OrderBookEntry& e : orders) {
		prodMap[e.product] = true;
	}
	for (const std::pair<std::string, bool>& prodStringBoolPair : prodMap) {
		products.push_back(prodStringBoolPair.first);
	}
	return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
												std::string product,
												std::string timestamp) 
{
	std::vector<OrderBookEntry> entries;
	for (OrderBookEntry& e : orders) {
		if (e.type == type && e.product == product && e.timestamp == timestamp) {
			entries.push_back(e);
		}
	}
	return entries;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders) 
{
	double max = orders[0].price;
	for (OrderBookEntry& e : orders) {
		if (e.price > max) max = e.price;
	}
	return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders) 
{
	double min = orders[0].price;
	for (OrderBookEntry& e : orders) {
		if (e.price < min) min = e.price;
	}
	return min;
}

std::string OrderBook::getEarliestTime() {
	std::string earliestTime = orders[0].timestamp;
	for (OrderBookEntry& e : orders) {
		if (e.timestamp < earliestTime) {
			earliestTime = e.timestamp;
		}
	}
	return earliestTime;
}

std::string OrderBook::getNextTime(const std::string& timestamp) {
	std::string next_timeframe = "";
	for (OrderBookEntry& e : orders) {
		if (e.timestamp > timestamp) {
			next_timeframe = e.timestamp;
			break;
		}
	}
	if (next_timeframe == "") next_timeframe = getEarliestTime();
	return next_timeframe;
}

double OrderBook::getAveragePrice(std::vector <OrderBookEntry>& orders) {
	double avg = 0;
	int len = orders.size();
	for (const OrderBookEntry& e : orders) {
		avg += e.price;
	}
	avg = avg / len;
	return avg;
}

void OrderBook::insertOrder(OrderBookEntry& order) {
	orders.push_back(order);
	std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestmp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp) {
	std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
	std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
	std::vector<OrderBookEntry> sales;

	std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
	std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

	for (OrderBookEntry& ask : asks) {
		for (OrderBookEntry& bid : bids) {
			if (bid.price >= ask.price) {
				OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::sale};
				if (bid.amount == ask.amount) {
					sale.amount = ask.amount;
					sales.push_back(sale);
					bid.amount = 0;
					break;
				}
				if (bid.amount > ask.amount) {
					sale.amount = ask.amount;
					sales.push_back(sale);
					bid.amount = bid.amount - ask.amount;
					break;
				}
				if (bid.amount < ask.amount) {
					sale.amount = bid.amount;
					sales.push_back(sale);
					ask.amount = ask.amount - bid.amount;
					bid.amount = 0;
					continue;
				}
			}
		}
	}
	return sales;
}