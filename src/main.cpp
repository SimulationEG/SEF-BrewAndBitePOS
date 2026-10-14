// main.cpp
// Brew & Bite Café POS: program entry point. main() only decides; functions do the work.
#include <iostream>
#include <iomanip>
#include <string>
#include "constants.h"
#include "types.h"
#include "input.h"
#include "logic.h"
#include "memory.h"
#include "screens.h"
#include "order.h"
#include "reports.h"
using namespace std;

int main() {
    cout << fixed << setprecision(2);

    // ---- menu: parallel dynamic arrays ----
    int capacity = 5, itemCount = 0;
    string* names = new string[capacity];
    double* prices = new double[capacity];
    int* stock = new int[capacity];
    Category* cats = new Category[capacity];
    int** weeklySales = new int*[DAYS];            // 2D: one row per day
    for (int d = 0; d < DAYS; d++)
        weeklySales[d] = new int[capacity]();      // () = all zeros

    addItem(names, prices, stock, cats, weeklySales, itemCount, capacity,
            "Latte", 37.5, Category::Drink, 50);
    addItem(names, prices, stock, cats, weeklySales, itemCount, capacity,
            "Espresso", 30, Category::Drink, 50);
    addItem(names, prices, stock, cats, weeklySales, itemCount, capacity,
            "Croissant", 40, Category::Food, 20);
    addItem(names, prices, stock, cats, weeklySales, itemCount, capacity,
            "Cheesecake", 65, Category::Dessert, 8);
    addItem(names, prices, stock, cats, weeklySales, itemCount, capacity,
            "Water", 10, Category::Drink, 100);

    // ---- customers: parallel dynamic arrays ----
    int custCapacity = 3, custCount = 0;
    string* custNames = new string[custCapacity];
    int* custPoints = new int[custCapacity];
    addCustomer(custNames, custPoints, custCount, custCapacity, "Ahmed", 120);
    addCustomer(custNames, custPoints, custCount, custCapacity, "Mona", 250);
    addCustomer(custNames, custPoints, custCount, custCapacity, "Omar", 600);

    // ---- shift counters: enum value = array index ----
    int ordersByType[TYPES] = {0};
    double revenueByPayment[METHODS] = {0};
    int receiptNo = 1001;

    cout << "=== Open shift ===\n";
    int day = readInt("Day (1=Sat ... 7=Fri): ", 1, DAYS) - 1;
    double openingCash = readDouble("Opening cash: ", 0);
    cout << "Shift opened: " << DAY_NAMES[day]
         << " with " << openingCash << " EGP\n";

    MenuOption choice;
    do {
        printMainMenu(day);
        choice = static_cast<MenuOption>(readInt("> ", 0, 9));
        switch (choice) {

            case MenuOption::ShowMenu:
                showMenu(names, prices, stock, cats, itemCount);
                break;

            case MenuOption::NewOrder:
                newOrder(names, prices, stock, cats, itemCount,
                         custNames, custPoints, custCount, weeklySales,
                         day, ordersByType, revenueByPayment, receiptNo);
                break;

            case MenuOption::AddItem: {
                string name = readName("Name: ");
                double price = readDouble("Price: ", 0.01);      // BR-1
                Category c = static_cast<Category>(
                    readInt("Category (0-Drink 1-Food 2-Dessert): ", 0, 2));
                int qty = readInt("Starting stock: ", 0, 100000);
                addItem(names, prices, stock, cats, weeklySales,
                        itemCount, capacity, name, price, c, qty);
                cout << "Added as ID " << itemCount << ".\n";
                break;
            }

            case MenuOption::Restock: {
                int id = readInt("Item ID: ", 1, 100000);
                int* p = findStock(stock, itemCount, id);
                if (p == nullptr) { cout << "Item not found.\n"; break; }
                int qty = readInt("Quantity received: ", 1, 100000);
                restock(*p, qty);                    // pointer -> reference
                cout << names[id - 1] << " stock is now " << *p << ".\n";
                break;
            }

            case MenuOption::ChangePrice:
                changePrice(names, prices, itemCount);
                break;

            case MenuOption::AddCustomer: {
                string name = readName("Customer name: ");
                addCustomer(custNames, custPoints, custCount,
                            custCapacity, name, 0);
                cout << "Customer ID " << custCount << " created.\n";
                break;
            }

            case MenuOption::ShowCustomers:
                showCustomers(custNames, custPoints, custCount);
                break;

            case MenuOption::CloseDay:
                closeDay(names, stock, itemCount, weeklySales, day,
                         ordersByType, revenueByPayment, openingCash);
                break;

            case MenuOption::WeeklyReport:
                weeklyReport(names, weeklySales, itemCount);
                break;

            case MenuOption::Exit: {                 // FR-12.1
                int open = 0;
                for (int t = 0; t < TYPES; t++) open += ordersByType[t];
                if (open > 0 && !readYesNo("Day not closed (" +
                        to_string(open) + " orders). Exit anyway? (y/n): "))
                    choice = MenuOption::ShowMenu;   // stay in the loop
                else
                    cout << "Goodbye!\n";
                break;
            }

        }
    } while (choice != MenuOption::Exit);

    // ---- give every heap block back ----
    for (int d = 0; d < DAYS; d++) delete[] weeklySales[d];  // rows first
    delete[] weeklySales;                            // then the row table
    delete[] names; delete[] prices; delete[] stock; delete[] cats;

    delete[] custNames; delete[] custPoints;

    return 0;
}
