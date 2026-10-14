// order.h
// Taking an order: cart, pricing pipeline, payment, commit, loyalty, receipt. (Steps 8-11)
#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "types.h"

void newOrder(const std::string* names, const double* prices, int* stock,
              const Category* cats, int itemCount,
              const std::string* custNames, int* custPoints, int custCount,
              int** sales, int day, int* ordersByType,
              double* revenueByPayment, int& receiptNo);

#endif // ORDER_H
