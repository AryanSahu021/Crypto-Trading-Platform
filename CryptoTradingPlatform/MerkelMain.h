#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
class MerkelMain
{
public:
    MerkelMain() = default;
    /** Call this to start the sim */
    void init();

private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterOffer();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);
    OrderBook orderBook{"C:\\Users\\aryan\\Downloads\\20200317.csv"};
    std::string curTime;
};
