// screens.cpp
// Console screens: menus and tables. (Steps 4-7)
#include "screens.h"
#include <iostream>
#include <iomanip>
#include "constants.h"
#include "helpers.h"
#include "input.h"
#include "logic.h"
using namespace std;

void showMenu(const string* names, const double* prices,
              const int* stock, const Category* cats, int count) {
    cout << left << setw(4) << "ID" << setw(14) << "Name"
         << setw(9) << "Category" << right << setw(9) << "Price"
         << setw(7) << "Stock" << "\n";
    for (int i = 0; i < count; i++) {
        cout << left << setw(4) << i + 1 << setw(14) << names[i]
             << setw(9) << categoryName(cats[i])
             << right << setw(9) << prices[i] << setw(7) << stock[i];
        if (stock[i] == 0) cout << "  OUT";
        else if (stock[i] <= REORDER_LEVEL) cout << "  LOW";
        cout << "\n";
    }
}

void printMainMenu(int day) {
    cout << "\n=== Brew & Bite POS  |  " << DAY_NAMES[day] << " ===\n"
         << "1) Show menu      2) New order       3) Add item\n"
         << "4) Restock        5) Change price    6) Add customer\n"
         << "7) Customers      8) Close day       9) Weekly report\n"
         << "0) Exit\n";
}

void changePrice(const string* names, double* prices, int count) {
    int id = readInt("Item ID: ", 1, 100000);
    double* p = findPrice(prices, count, id);
    if (p == nullptr) { cout << "Item not found.\n"; return; }
    double newPrice = readDouble("New price: ", 0.01);
    double change = (newPrice - *p) / *p;          // relative change
    if (change < 0) change = -change;
    if (change > MAX_PRICE_CHANGE &&
        !readYesNo("  Change is more than 30%. Are you sure? (y/n): ")) {
        cout << "Price not changed.\n";
        return;
    }
    cout << names[id - 1] << ": " << *p << " -> " << newPrice << "\n";
    *p = newPrice;                                 // write through pointer
}

void showCustomers(const string* custNames, const int* custPoints,
                   int count) {
    cout << left << setw(4) << "ID" << setw(14) << "Name"
         << right << setw(8) << "Points" << "  Tier\n";
    for (int i = 0; i < count; i++)
        cout << left << setw(4) << i + 1 << setw(14) << custNames[i]
             << right << setw(8) << custPoints[i] << "  "
             << tierName(tierOf(custPoints[i])) << "\n";
}
