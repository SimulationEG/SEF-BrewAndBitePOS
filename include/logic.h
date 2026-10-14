// logic.h
// Pointers, references and pass by value. (Steps 6, 9, 10)
#ifndef LOGIC_H
#define LOGIC_H

// Return the address of an item, or nullptr when the ID is not valid.
int* findStock(int* stock, int count, int id);
double* findPrice(double* prices, int count, int id);

void restock(int& itemStock, int qty);          // by reference: works
void restockWrong(int itemStock, int qty);      // by value: changes a copy (exercise)
void sellItem(int& itemStock, int qty);

void applyDiscount(double& amount, double discount);  // modifies the caller
double calcServiceCharge(double amount);              // returns a result
double calcVAT(double amount);

// Returns false if not enough cash; the change comes back through 'change'.
bool payWithCash(double total, double& change);

#endif // LOGIC_H
