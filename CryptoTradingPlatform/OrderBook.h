#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include <string>
class OrderBook
{
public:
	/**Construct, Reading a csv file */
	OrderBook(std::string filename);
	/**Return vector of all known products in the orderbook */
	std::vector<std::string> getKnownProducts();
	/**Return vector of Orders according to sent filters */
	std::vector<OrderBookEntry> getOrders(OrderBookType type,
										  std::string product,
										  std::string timestamp);
	/**Return price of highest bid in the sent set */
	static double getHighPrice(std::vector<OrderBookEntry>& orders);
	/**Return price of lowest bid in the sent set */
	static double getLowPrice(std::vector<OrderBookEntry>& orders);
	/**Returns the earliest time in orderbook */
	std::string getEarliestTime();
	/**Returns the next time frame */
	std::string getNextTime(const std::string& timestamp);
	/**Returns the average price in that timeframe */
	static double getAveragePrice(std::vector<OrderBookEntry>& orders);
	void insertOrder(OrderBookEntry& order);
	std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);
private:
	std::vector<OrderBookEntry> orders;
};

