#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <iomanip>
using namespace std;

struct Stock {
    string symbol;
    int quantity;
    double price;
};

unordered_map<string, Stock> loadPortfolio(const string &filename)
{
    unordered_map<string, Stock> portfolio;
    ifstream inFile(filename);

    if (inFile.is_open()) {
        string symbol;
        int quantity;
        double price;

        while (inFile >> symbol >> quantity >> price) {
            portfolio[symbol] = {symbol, quantity, price};
        }
        inFile.close();
    }
    return portfolio;
}

void savePortfolio(const unordered_map<string, Stock> &portfolio, const string &filename)
{
    ofstream outFile(filename);

    if (outFile.is_open()) {
        for (const auto &pair : portfolio) {
            outFile << pair.second.symbol << " "
                    << pair.second.quantity << " "
                    << fixed << setprecision(2)
                    << pair.second.price << endl;
        }
        outFile.close();
    }
}

void buyStock(unordered_map<string, Stock> &portfolio, const string &symbol, int quantity, double price)
{
    if (portfolio.find(symbol) != portfolio.end()) {
        portfolio[symbol].quantity += quantity;
        portfolio[symbol].price = price;
    } else {
        portfolio[symbol] = {symbol, quantity, price};
    }
    cout << "Bought " << quantity << " shares of " << symbol
         << " at " << fixed << setprecision(2) << price << " each." << endl;
}

void sellStock(unordered_map<string, Stock> &portfolio, const string &symbol, int quantity)
{
    if (portfolio.find(symbol) != portfolio.end() && portfolio[symbol].quantity >= quantity) {
        portfolio[symbol].quantity -= quantity;

        if (portfolio[symbol].quantity == 0) {
            portfolio.erase(symbol);
        }
        cout << "Sold " << quantity << " shares of " << symbol << "." << endl;
    } else {
        cout << "Not enough shares to sell or stock not found in portfolio." << endl;
    }
}

void viewPortfolio(const unordered_map<string, Stock> &portfolio)
{
    cout << "Portfolio:" << endl;
    cout << "Symbol\tQuantity\tPrice" << endl;

    for (const auto &pair : portfolio) {
        cout << pair.second.symbol << "\t"
             << pair.second.quantity << "\t\t"
             << fixed << setprecision(2) << pair.second.price << endl;
    }
}

int main()
{
    unordered_map<string, Stock> portfolio = loadPortfolio("portfolio.txt");
    int choice;
    string symbol;
    int quantity;
    double price;

    do {
        cout << "\nTrading Application Menu:" << endl;
        cout << "1. Buy Stock" << endl;
        cout << "2. Sell Stock" << endl;
        cout << "3. View Portfolio" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter stock symbol: ";
                cin >> symbol;
                cout << "Enter quantity: ";
                cin >> quantity;
                cout << "Enter price: ";
                cin >> price;
                buyStock(portfolio, symbol, quantity, price);
                break;
            case 2:
                cout << "Enter stock symbol: ";
                cin >> symbol;
                cout << "Enter quantity: ";
                cin >> quantity;
                sellStock(portfolio, symbol, quantity);
                break;
            case 3:
                viewPortfolio(portfolio);
                break;
            case 4:
                savePortfolio(portfolio, "portfolio.txt");
                cout << "Portfolio saved. Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
