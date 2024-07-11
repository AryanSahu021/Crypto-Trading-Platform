#include <iostream>
#include <vector>
#include "MerkelMain.h"
#include "CSVReader.h"

void MerkelMain::init() {
    int input;
    curTime = orderBook.getEarliestTime();
    wallet.insertCurrency("BTC", 10);
    while (true) {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    std::cout << "Welcome!!" << std::endl;
    std::cout << "Choose from the following options" << std::endl;
    std::cout << "1- Print Help" << std::endl;
    std::cout << "2- Print Exchange stats" << std::endl;
    std::cout << "3- Place an ask" << std::endl;
    std::cout << "4- Place a bid" << std::endl;
    std::cout << "5- Print Wallet" << std::endl;
    std::cout << "6- Go to next timeframe" << std::endl;
    std::cout << "============================" << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help menu here!!" << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (const std::string& p : orderBook.getKnownProducts()) {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, curTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
        std::cout << "Average ask: " << OrderBook::getAveragePrice(entries) << std::endl;
    }
}

void MerkelMain::enterAsk()
{   
    std::string input;
    std::cout << "Enter Ask: (Product,Price,Amount e.g ETH/BTC,200,0.5): " << std::endl;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                curTime,
                tokens[0],
                OrderBookType::ask
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe)) {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds. " << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "MerkelMain::enterAsk : Bad Input! " << std::endl;
            }
    }

}

void MerkelMain::enterBid()
{
    std::string input;
    std::cout << "Enter Bid: (Product,Price,Amount e.g ETH/BTC,200,0.5): " << std::endl;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                curTime,
                tokens[0],
                OrderBookType::bid
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe)) {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds. " << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "MerkelMain::enterBid : Bad Input! " << std::endl;
        }
    }
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame..." << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", curTime);
    std::cout << "Sales: " << sales.size() << std::endl;
    for (OrderBookEntry& sale : sales) {
        std::cout << "Sale Price: " << sale.price << " Amount: " << sale.amount << std::endl;
        if (sale.username == "simuser") {
            // Update the wallet.
            wallet.processSale(sale);
        }
    }
    curTime = orderBook.getNextTime(curTime);
}

int MerkelMain::getUserOption()
{   
    int userOption = 0;
    std::cout << "Type in 1-6" << std::endl;
    std::string line;
    std::getline(std::cin, line);
    try {
        userOption = std::stoi(line);
    }
    catch (const std::exception& e) {
        //
    }
    return userOption;
}

void MerkelMain::processUserOption(int choice)
{
    switch (choice)
    {
    case 1:
        printHelp();
        break;
    case 2:
        printMarketStats();
        break;
    case 3:
        enterAsk();
        break;
    case 4:
        enterBid();
        break;
    case 5:
        printWallet();
        break;
    case 6:
        gotoNextTimeframe();
        break;
    default:
        std::cout << "Invalid Choice!" << std::endl;
        break;
    }
}