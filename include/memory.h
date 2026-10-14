// memory.h
// Dynamic arrays that grow: allocate, copy, free, re-point. (Steps 4, 7, 8)
#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include "types.h"

void growMenu(std::string*& names, double*& prices, int*& stock,
              Category*& cats, int** sales, int count, int& capacity);
void addItem(std::string*& names, double*& prices, int*& stock,
             Category*& cats, int** sales, int& count, int& capacity,
             const std::string& name, double price, Category c, int qty);
void addCustomer(std::string*& custNames, int*& custPoints, int& count,
                 int& capacity, const std::string& name, int points);
void freeCart(int* ids, int* qty, Size* sizes, double* totals);

#endif // MEMORY_H
