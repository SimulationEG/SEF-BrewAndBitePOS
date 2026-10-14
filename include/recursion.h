// recursion.h
// Receipt check digit using recursion. (Step 11)
#ifndef RECURSION_H
#define RECURSION_H

int digitSum(int n);            // recursive: last digit + digitSum(rest)
int checkDigit(int receiptNo);  // FR-9.1: digitSum % 10

#endif // RECURSION_H
