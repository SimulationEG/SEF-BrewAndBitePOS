// logic.cpp
// Pointers, references and pass by value. (Steps 6, 9, 10)
#include "logic.h"
#include <iostream>
#include "constants.h"
#include "input.h"
using namespace std;

int* findStock(int* stock, int count, int id) {    // nullptr = not found
    if (id < 1 || id > count) return nullptr;
    return stock + (id - 1);                        // pointer arithmetic
}

double* findPrice(double* prices, int count, int id) {
    if (id < 1 || id > count) return nullptr;
    return &prices[id - 1];                         // same idea with &
}

void restock(int& itemStock, int qty) {        // by reference: works
    itemStock += qty;
}

void restockWrong(int itemStock, int qty) {    // by value: changes a copy
    itemStock += qty;                          // (kept for the exercise)
}

void applyDiscount(double& amount, double discount) {  // changes caller
    amount -= discount;
}

double calcServiceCharge(double amount) {     // by value: returns result
    return amount * SERVICE_RATE;
}

double calcVAT(double amount) {
    return amount * VAT_RATE;
}

void sellItem(int& itemStock, int qty) {
    itemStock -= qty;
}

bool payWithCash(double total, double& change) {  // change is an output
    double paid = readDouble("Cash received: ", 0);
    if (paid < total) {
        cout << "  Not enough, " << (total - paid) << " EGP missing.\n";
        return false;
    }
    change = paid - total;
    return true;
}
