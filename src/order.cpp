// order.cpp
// Taking an order: cart, pricing pipeline, payment, commit, loyalty, receipt. (Steps 8-11)
#include "order.h"
#include <iostream>
#include <iomanip>
#include "constants.h"
#include "helpers.h"
#include "input.h"
#include "logic.h"
#include "recursion.h"
#include "memory.h"
using namespace std;

void newOrder(const string* names, const double* prices, int* stock,
              const Category* cats, int itemCount,
              const string* custNames, int* custPoints, int custCount,
              int** sales, int day, int* ordersByType,
              double* revenueByPayment, int& receiptNo) {
    if (itemCount == 0) { cout << "Menu is empty.\n"; return; }

    // ---- 1. order type and customer ----
    OrderType type = static_cast<OrderType>(
        readInt("Order type (0-Dine in 1-Takeaway 2-Delivery): ", 0, 2));
    int custId = readInt("Customer ID (0 = guest): ", 0, custCount);
    int* points = nullptr;                        // nullptr = guest
    if (custId > 0) {
        points = &custPoints[custId - 1];
        cout << "  " << custNames[custId - 1] << " | "
             << tierName(tierOf(*points)) << " | " << *points << " pts\n";
    }

    // ---- 2. cart: size known only at run time ----
    int lines = readInt("How many different items? ", 1, MAX_LINES);
    int* cartIds = new int[lines];
    int* cartQty = new int[lines];
    Size* cartSizes = new Size[lines];
    double* lineTotals = new double[lines];

    for (int i = 0; i < lines; i++) {
        bool valid = false;
        while (!valid) {
            int id = readInt("Item ID: ", 1, 100000);
            int* itemStock = findStock(stock, itemCount, id);
            if (itemStock == nullptr) {
                cout << "  -> Item not found, try again.\n";
                continue;
            }
            int idx = id - 1;
            Size size = Size::Small;
            if (cats[idx] == Category::Drink)
                size = static_cast<Size>(readInt("Size (0-S 1-M 2-L): ", 0, 2));
            int qty = readInt("Qty: ", 1, MAX_QTY);

            int reserved = 0;            // same item already in this cart
            for (int j = 0; j < i; j++)
                if (cartIds[j] == id) reserved += cartQty[j];
            if (qty + reserved > *itemStock) {
                cout << "  -> Not enough stock (available "
                     << *itemStock - reserved << ").\n";
                continue;
            }
            cartIds[i] = id;
            cartQty[i] = qty;
            cartSizes[i] = size;
            lineTotals[i] = prices[idx] * sizeFactor(size) * qty;
            cout << "  -> " << names[idx] << " x" << qty
                 << " = " << lineTotals[i] << "\n";
            valid = true;
        }
    }

    // ---- 3. subtotal and counts ----
    double subtotal = 0, drinksTotal = 0;
    int drinkUnits = 0, dessertUnits = 0;
    for (int i = 0; i < lines; i++) {
        subtotal += lineTotals[i];
        Category c = cats[cartIds[i] - 1];
        if (c == Category::Drink) {
            drinksTotal += lineTotals[i];
            drinkUnits += cartQty[i];
        } else if (c == Category::Dessert) {
            dessertUnits += cartQty[i];
        }
    }

    if (type == OrderType::Delivery && subtotal < DELIVERY_MIN) {
        cout << "  Delivery needs at least " << DELIVERY_MIN
             << " EGP (subtotal " << subtotal << ").\n";
        if (readYesNo("  Switch to Takeaway? (y/n): ")) {
            type = OrderType::Takeaway;
        } else {
            cout << "Order cancelled.\n";
            freeCart(cartIds, cartQty, cartSizes, lineTotals);
            return;
        }
    }

    // ---- 4. pricing pipeline (the order matters!) ----
    double amount = subtotal;                                // step 1
    int combos = drinkUnits < dessertUnits ? drinkUnits : dessertUnits;
    double comboOff = combos * COMBO_DISCOUNT;
    if (comboOff > amount) comboOff = amount;
    applyDiscount(amount, comboOff);                         // step 2

    double discount = 0;                     // only the highest one wins
    string reason = "none";
    if (points != nullptr) {
        Tier t = tierOf(*points);
        if (amount * tierDiscountRate(t) > discount) {
            discount = amount * tierDiscountRate(t);
            reason = tierName(t) + " member";
        }
    }
    if (readYesNo("Student card? (y/n): ") &&
        amount * STUDENT_RATE > discount) {
        discount = amount * STUDENT_RATE;
        reason = "student 15%";
    }

    int hour = readInt("Hour (0-23): ", 0, 23);
    if (hour >= HAPPY_START && hour <= HAPPY_END &&
        drinksTotal * HAPPY_HOUR_RATE > discount) {
        discount = drinksTotal * HAPPY_HOUR_RATE;
        reason = "happy hour 20% drinks";
    }
    applyDiscount(amount, discount);                         // step 3

    double service = (type == OrderType::DineIn)
                     ? calcServiceCharge(amount) : 0;        // step 4
    amount += service;
    double vat = calcVAT(amount);                            // step 5
    amount += vat;
    double delivery = (type == OrderType::Delivery)
                      ? DELIVERY_FEE : 0;                    // step 6
    amount += delivery;

    cout << "\nSubtotal:     " << setw(10) << subtotal << "\n"
         << "Combo x" << combos << ":     -" << setw(9) << comboOff << "\n"
         << "Discount:     -" << setw(9) << discount
         << "  (" << reason << ")\n"
         << "Service 12%:  " << setw(10) << service << "\n"
         << "VAT 14%:      " << setw(10) << vat << "\n"
         << "Delivery fee: " << setw(10) << delivery << "\n"
         << "TOTAL:        " << setw(10) << amount << "\n";

    if (!readYesNo("Confirm order? (y/n): ")) {
        cout << "Order cancelled. Nothing was charged.\n";
        freeCart(cartIds, cartQty, cartSizes, lineTotals);
        return;
    }

    // ---- 5. payment ----
    Payment method = static_cast<Payment>(
        readInt("Payment (0-Cash 1-Card 2-Wallet): ", 0, 2));
    double change = 0;
    switch (method) {
        case Payment::Cash:
            while (!payWithCash(amount, change)) {}   // ask again
            cout << "Change: " << change << "\n";
            break;
        case Payment::Card: {
            double fee = amount * CARD_FEE_RATE;      // step 7
            amount += fee;
            cout << "Card fee 1%: " << fee << " -> charged " << amount << "\n";
            break;
        }
        case Payment::Wallet:
            cout << "Wallet payment: double points!\n";
            break;
    }

    // ---- 6. commit: only now touch stock and reports ----
    for (int i = 0; i < lines; i++) {
        int idx = cartIds[i] - 1;
        int& itemStock = stock[idx];              // reference = alias
        sellItem(itemStock, cartQty[i]);
        sales[day][idx] += cartQty[i];
        if (itemStock <= REORDER_LEVEL)
            cout << "  ! LOW STOCK: " << names[idx]
                 << " (" << itemStock << " left)\n";
    }
    ordersByType[static_cast<int>(type)]++;
    revenueByPayment[static_cast<int>(method)] += amount;

    // ---- 7. loyalty ----
    int earned = 0;
    if (points != nullptr) {
        earned = static_cast<int>(amount / 10);
        if (method == Payment::Wallet) earned *= 2;
        Tier before = tierOf(*points);
        *points += earned;                    // writes into custPoints
        if (tierOf(*points) != before)
            cout << "  * Upgraded to " << tierName(tierOf(*points)) << "!\n";
    }

    // ---- 8. receipt ----
    cout << "\n------ RECEIPT #" << receiptNo << "-"
         << checkDigit(receiptNo) << " ------\n"
         << DAY_NAMES[day] << " | " << orderTypeName(type)
         << " | " << paymentName(method) << "\n";
    const double* p = lineTotals;         // walk with pointer arithmetic
    for (int i = 0; i < lines; i++, p++) {
        int idx = cartIds[i] - 1;
        string label = names[idx];
        if (cats[idx] == Category::Drink)
            label += " (" + sizeName(cartSizes[i]) + ")";
        cout << left << setw(18) << label << " x" << setw(4) << cartQty[i]
             << right << setw(10) << *p << "\n";
    }
    cout << "Paid: " << amount;
    if (method == Payment::Cash) cout << " | Change: " << change;
    cout << "\n";
    if (points != nullptr)
        cout << "Points earned: " << earned
             << " | Balance: " << *points << "\n";
    cout << "--------------------------------\n";
    receiptNo++;

    freeCart(cartIds, cartQty, cartSizes, lineTotals);
}
