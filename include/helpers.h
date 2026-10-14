// helpers.h
// enum helpers and small business-rule functions. (Step 2)
#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include "types.h"

std::string categoryName(Category c);
std::string sizeName(Size s);
std::string orderTypeName(OrderType t);
std::string paymentName(Payment p);
std::string tierName(Tier t);
double sizeFactor(Size s);              // BR-6: drinks only
Tier tierOf(int points);                // FR-8.2
double tierDiscountRate(Tier t);

#endif // HELPERS_H
