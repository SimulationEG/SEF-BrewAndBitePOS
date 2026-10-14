// input.h
// Safe keyboard input: never crashes on bad input. (Step 3)
#ifndef INPUT_H
#define INPUT_H

#include <string>

void clearLine();
int readInt(const std::string& prompt, int minV, int maxV);
double readDouble(const std::string& prompt, double minV);
bool readYesNo(const std::string& prompt);
std::string readName(const std::string& prompt);

#endif // INPUT_H
