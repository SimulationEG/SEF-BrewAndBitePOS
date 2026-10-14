// memory.cpp
// Dynamic arrays that grow: allocate, copy, free, re-point. (Steps 4, 7, 8)
#include "memory.h"
#include <iostream>
#include "constants.h"
using namespace std;

void growMenu(string*& names, double*& prices, int*& stock,
              Category*& cats, int** sales, int count, int& capacity) {
    int newCap = capacity * 2;
    string* n2 = new string[newCap];                 // 1. allocate
    double* p2 = new double[newCap];
    int* s2 = new int[newCap];
    Category* c2 = new Category[newCap];
    for (int i = 0; i < count; i++) {                // 2. copy
        n2[i] = names[i]; p2[i] = prices[i];
        s2[i] = stock[i]; c2[i] = cats[i];
    }
    delete[] names; delete[] prices;                 // 3. free
    delete[] stock; delete[] cats;
    names = n2; prices = p2; stock = s2; cats = c2;  // 4. re-point

    for (int d = 0; d < DAYS; d++) {        // grow every row of the grid
        int* row = new int[newCap]();
        for (int i = 0; i < count; i++) row[i] = sales[d][i];
        delete[] sales[d];
        sales[d] = row;
    }

    capacity = newCap;
    cout << "  (menu capacity grown to " << capacity << ")\n";
}

void addItem(string*& names, double*& prices, int*& stock,
             Category*& cats, int** sales, int& count, int& capacity,
             const string& name, double price, Category c, int qty) {
    if (count == capacity)
        growMenu(names, prices, stock, cats, sales, count, capacity);
    names[count] = name;
    prices[count] = price;
    stock[count] = qty;
    cats[count] = c;
    count++;
}

void addCustomer(string*& custNames, int*& custPoints, int& count,
                 int& capacity, const string& name, int points) {
    if (count == capacity) {
        int newCap = capacity * 2;
        string* n2 = new string[newCap];
        int* p2 = new int[newCap];
        for (int i = 0; i < count; i++) {
            n2[i] = custNames[i];
            p2[i] = custPoints[i];
        }
        delete[] custNames; delete[] custPoints;
        custNames = n2; custPoints = p2;
        capacity = newCap;
    }
    custNames[count] = name;
    custPoints[count] = points;
    count++;
}

void freeCart(int* ids, int* qty, Size* sizes, double* totals) {
    delete[] ids; delete[] qty; delete[] sizes; delete[] totals;
}
