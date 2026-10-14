// reports.cpp
// Closing report with drawer check, and the weekly report. (Step 12)
#include "reports.h"
#include <iostream>
#include <iomanip>
#include "constants.h"
#include "types.h"
#include "helpers.h"
#include "input.h"
using namespace std;

void closeDay(const string* names, const int* stock, int itemCount,
              int** sales, int& day, int* ordersByType,
              double* revenueByPayment, double& openingCash) {
    int totalOrders = 0;
    double totalRevenue = 0;
    for (int t = 0; t < TYPES; t++) totalOrders += ordersByType[t];
    for (int m = 0; m < METHODS; m++) totalRevenue += revenueByPayment[m];

    cout << "\n===== CLOSING REPORT: " << DAY_NAMES[day] << " =====\n";
    cout << "Orders: " << totalOrders << "\n";
    for (int t = 0; t < TYPES; t++)
        cout << "  " << left << setw(10)
             << orderTypeName(static_cast<OrderType>(t))
             << right << setw(5) << ordersByType[t] << "\n";
    cout << "Revenue: " << totalRevenue << "\n";
    for (int m = 0; m < METHODS; m++)
        cout << "  " << left << setw(10) << paymentName(static_cast<Payment>(m))
             << right << setw(10) << revenueByPayment[m] << "\n";
    if (totalOrders > 0)
        cout << "Average order: " << totalRevenue / totalOrders << "\n";

    // ---- cash drawer check ----
    double expected = openingCash
                    + revenueByPayment[static_cast<int>(Payment::Cash)];
    cout << "Expected cash in drawer: " << expected << "\n";
    double counted = readDouble("Cash counted: ", 0);
    double diff = counted - expected;
    if (diff > 0.005)       cout << "  Drawer OVER by " << diff << "\n";
    else if (diff < -0.005) cout << "  Drawer SHORT by " << -diff << "\n";
    else                    cout << "  Drawer balanced.\n";

    // ---- best seller today: one row of the 2D grid ----
    int best = -1, bestUnits = 0;
    for (int i = 0; i < itemCount; i++)
        if (sales[day][i] > bestUnits) {
            bestUnits = sales[day][i];
            best = i;
        }
    if (best != -1) cout << "Best seller today: " << names[best]
                         << " (" << bestUnits << " units)\n";
    else            cout << "No items sold today.\n";

    // ---- reorder list ----
    cout << "Reorder list:\n";
    bool any = false;
    for (int i = 0; i < itemCount; i++)
        if (stock[i] <= REORDER_LEVEL) {
            cout << "  - " << names[i] << " (" << stock[i] << ")\n";
            any = true;
        }
    if (!any) cout << "  (nothing)\n";

    // ---- reset and move to the next day ----
    for (int t = 0; t < TYPES; t++) ordersByType[t] = 0;
    for (int m = 0; m < METHODS; m++) revenueByPayment[m] = 0;
    day = (day + 1) % DAYS;
    openingCash = readDouble("Opening cash for " + DAY_NAMES[day] + ": ", 0);
}

void weeklyReport(const string* names, int** sales, int count) {
    int worstDay = 0, worstTotal = -1;
    for (int d = 0; d < DAYS; d++) {                // row by row
        int dayTotal = 0;
        for (int i = 0; i < count; i++) dayTotal += sales[d][i];
        cout << DAY_NAMES[d] << ": " << dayTotal << " units\n";
        if (worstTotal == -1 || dayTotal < worstTotal) {
            worstTotal = dayTotal;
            worstDay = d;
        }
    }
    int best = 0, bestTotal = -1;
    for (int i = 0; i < count; i++) {               // column by column
        int itemTotal = 0;
        for (int d = 0; d < DAYS; d++) itemTotal += sales[d][i];
        if (itemTotal > bestTotal) { bestTotal = itemTotal; best = i; }
    }
    if (count > 0) cout << "Best seller of the week: " << names[best]
                        << " (" << bestTotal << " units)\n";
    cout << "Weakest day: " << DAY_NAMES[worstDay]
         << " (" << worstTotal << " units)\n";
}
