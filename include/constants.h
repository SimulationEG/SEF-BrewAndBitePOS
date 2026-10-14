// constants.h
// Business constants (one place to change any rule value).
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// Business rules (BR) and requirements (FR) as named constants.
const double VAT_RATE        = 0.14;   // 14% VAT
const double SERVICE_RATE    = 0.12;   // dine in only
const double CARD_FEE_RATE   = 0.01;   // card payments
const double DELIVERY_FEE    = 25.0;   // EGP, no VAT on it
const double DELIVERY_MIN    = 100.0;  // minimum delivery subtotal
const double COMBO_DISCOUNT  = 10.0;   // per drink + dessert pair
const double STUDENT_RATE    = 0.15;
const double HAPPY_HOUR_RATE = 0.20;   // drinks only
const int HAPPY_START = 15, HAPPY_END = 17;
const int SILVER_POINTS = 200, GOLD_POINTS = 500;
const int REORDER_LEVEL = 5;
const int MAX_LINES = 10, MAX_QTY = 20;
const double MAX_PRICE_CHANGE = 0.30;
const int DAYS = 7, TYPES = 3, METHODS = 3;
const std::string DAY_NAMES[DAYS] =
    {"Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"};

#endif // CONSTANTS_H
