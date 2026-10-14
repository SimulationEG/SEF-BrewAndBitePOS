// helpers.cpp
// enum helpers and small business-rule functions. (Step 2)
#include "helpers.h"
#include "constants.h"
using namespace std;

string categoryName(Category c) {
    switch (c) {
        case Category::Drink:   return "Drink";
        case Category::Food:    return "Food";
        case Category::Dessert: return "Dessert";
    }
    return "?";
}

string sizeName(Size s) {
    switch (s) {
        case Size::Small:  return "S";
        case Size::Medium: return "M";
        case Size::Large:  return "L";
    }
    return "?";
}

string orderTypeName(OrderType t) {
    switch (t) {
        case OrderType::DineIn:   return "Dine in";
        case OrderType::Takeaway: return "Takeaway";
        case OrderType::Delivery: return "Delivery";
    }
    return "?";
}

string paymentName(Payment p) {
    switch (p) {
        case Payment::Cash:   return "Cash";
        case Payment::Card:   return "Card";
        case Payment::Wallet: return "Wallet";
    }
    return "?";
}

string tierName(Tier t) {
    switch (t) {
        case Tier::Regular: return "Regular";
        case Tier::Silver:  return "Silver";
        case Tier::Gold:    return "Gold";
    }
    return "?";
}

double sizeFactor(Size s) {      // BR-6: drinks only
    switch (s) {
        case Size::Small:  return 1.0;
        case Size::Medium: return 1.25;
        case Size::Large:  return 1.5;
    }
    return 1.0;
}

Tier tierOf(int points) {             // FR-8.2
    if (points >= GOLD_POINTS) return Tier::Gold;
    else if (points >= SILVER_POINTS) return Tier::Silver;
    else return Tier::Regular;
}

double tierDiscountRate(Tier t) {
    switch (t) {
        case Tier::Regular: return 0.0;
        case Tier::Silver:  return 0.05;
        case Tier::Gold:    return 0.10;
    }
    return 0.0;
}
