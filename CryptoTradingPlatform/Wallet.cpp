#include "Wallet.h"
#include "CSVReader.h"

Wallet::Wallet() {

}

void Wallet::insertCurrency(std::string type, double amount) {
	double balance;
	if (amount < 0) {
		throw std::exception{};
	}
	if (currencies.count(type) == 0) {
		balance = 0;
	}
	else {
		balance = currencies[type];
	}
	balance += amount;
	currencies[type] = balance;
}

std::string Wallet::toString() {
	std::string s;
	for (std::pair<std::string, double> pair : currencies) {
		std::string currency = pair.first;
		double amount = pair.second;
		s += currency + " : " + std::to_string(amount) + "\n";
	}
	return s;
}

bool Wallet::containsCurrency(std::string type, double amount) {
	if (currencies.count(type) == 0) {
		return false;
	}
	else {
		return currencies[type] >= amount;
	}
}

bool Wallet::removeCurrency(std::string type, double amount) {
	if (amount < 0) {
		return false;
	}
	if (currencies.count(type) == 0) {
		return false;
	}
	else {
		if (containsCurrency(type, amount)) {
			currencies[type] -= amount;
			return true;
		}
		else return false;
	}
}

bool Wallet::canFulfillOrder(OrderBookEntry order) {
	std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
	//ask
	if (order.type == OrderBookType::ask) {
		double amount = order.amount;
		std::string currency = currs[0];
		return containsCurrency(currency, amount);
	}
	// bid
	if (order.type == OrderBookType::bid) {
		double amount = order.amount * order.price;
		std::string currency = currs[1];
		return containsCurrency(currency, amount);
	}
}

void Wallet::processSale(OrderBookEntry& sale) {
	std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');
	//ask
	if (sale.type == OrderBookType::asksale) {
		double outgoingAmount = sale.amount;
		std::string outgoingCurrency = currs[0];
		double incomingAmount = sale.amount * sale.price;
		std::string incomingCurrency = currs[1];
		currencies[incomingCurrency] += incomingAmount;
		currencies[outgoingCurrency] -= outgoingAmount;
	}
	// bid
	if (sale.type == OrderBookType::bidsale) {
		double incomingAmount = sale.amount;
		std::string incomingCurrency = currs[0];
		double outgoingAmount = sale.amount * sale.price;
		std::string outgoingCurrency = currs[1];
		currencies[incomingCurrency] += incomingAmount;
		currencies[outgoingCurrency] -= outgoingAmount;
	}
}