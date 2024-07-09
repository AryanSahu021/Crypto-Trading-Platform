#include <iostream>
#include <vector>
#include "MerkelMain.h"
#include "CSVReader.h"

void MerkelMain::init() {
    int input;
    curTime = orderBook.getEarliestTime();
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
    std::cout << "6- Continue" << std::endl;
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

void MerkelMain::enterOffer()
{
    std::cout << "Placing an ask on..." << std::endl;
}

void MerkelMain::enterBid()
{
    std::cout << "Placing a bid on..." << std::endl;
}

void MerkelMain::printWallet()
{
    std::cout << " Sorry you are broke. Your wallet is empty." << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame..." << std::endl;
    curTime = orderBook.getNextTime(curTime);
}

int MerkelMain::getUserOption()
{
    std::cout << "Type in 1-6" << std::endl;
    int choice;
    std::cin >> choice;
    return choice;
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
        enterOffer();
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