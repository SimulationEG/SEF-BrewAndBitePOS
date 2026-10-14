// reports.h
// Closing report with drawer check, and the weekly report. (Step 12)
#ifndef REPORTS_H
#define REPORTS_H

#include <string>

void closeDay(const std::string* names, const int* stock, int itemCount,
              int** sales, int& day, int* ordersByType,
              double* revenueByPayment, double& openingCash);
void weeklyReport(const std::string* names, int** sales, int count);

#endif // REPORTS_H
