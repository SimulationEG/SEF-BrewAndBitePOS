// recursion.cpp
// Receipt check digit using recursion. (Step 11)
#include "recursion.h"

int digitSum(int n) {
    if (n < 10) return n;                  // base case: one digit
    return n % 10 + digitSum(n / 10);      // last digit + the rest
}

int checkDigit(int receiptNo) {            // FR-9.1
    return digitSum(receiptNo) % 10;
}
