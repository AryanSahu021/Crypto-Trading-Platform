#include "CSVReader.h"
#include <fstream>
CSVReader::CSVReader() {

}
std::vector<OrderBookEntry> CSVReader::readCSV(const std::string csvFile) {
	std::vector<OrderBookEntry> entries;
    std::ifstream csvfile{csvFile};
    if (csvfile.is_open()) {
        std::cout << "File Opened Successfully" << std::endl;
        std::string csvline;
        while (std::getline(csvfile, csvline)) {
            std::vector<std::string> tokens;
            tokens = tokenise(csvline, ',');
            try {
                OrderBookEntry entry = stringsToOBE(tokens);
                entries.push_back(entry);
            }
            catch (const std::exception& e) {
                continue;
            }
        }
        csvfile.close();
    }
    else {
        std::cout << "Failed to open file" << std::endl;
    }
    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char seperator) {
    std::vector<std::string> tokens;
    std::string token;
    signed int start, end;
    start = csvLine.find_first_not_of(seperator, 0);
    do {
        end = csvLine.find_first_of(seperator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while (end != std::string::npos);
    return tokens;
}


OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens) {
    if (tokens.size() != 5) {
        // bad row
        std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }
    double price, amount;
    std::string timestamp, product;
    OrderBookType type;
    try {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (const std::exception& e) {
        std::cout << "Bad Float: " << tokens[3] << std::endl;
        std::cout << "Bad Float: " << tokens[4] << std::endl;
        throw;
    }
    timestamp = tokens[0];
    product = tokens[1];
    type = OrderBookEntry::stringToOrderBookType(tokens[2]);
    OrderBookEntry entry = OrderBookEntry(price, amount, timestamp, product, type);
    return entry;
}
