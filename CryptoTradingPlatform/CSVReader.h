#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <iostream>
class CSVReader
{
public:
	CSVReader();
	/** parse the sent CSV file into multiple
	* OrderBookEntry objects which should contain
	* lines like:
	* 2020/03/17 17:01:24.884492,ETH/BTC,bid,0.02187305,6.85567013
	*/
	static std::vector<OrderBookEntry> readCSV(const std::string csvFile);
private:
	static std::vector<std::string> tokenise(std::string csvLine, char seperator);
	static OrderBookEntry stringsToOBE(std::vector<std::string> tokens);
};

