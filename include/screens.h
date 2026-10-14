// screens.h
// Console screens: menus and tables. (Steps 4-7)
#ifndef SCREENS_H
#define SCREENS_H

#include <string>
#include "types.h"

void showMenu(const std::string* names, const double* prices,
              const int* stock, const Category* cats, int count);
void printMainMenu(int day);
void changePrice(const std::string* names, double* prices, int count);
void showCustomers(const std::string* custNames, const int* custPoints,
                   int count);

#endif // SCREENS_H
