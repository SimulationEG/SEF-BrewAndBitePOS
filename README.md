# Brew & Bite Café POS (C++)

A console point-of-sale program for a small café, built for the C++ course final project.
Concepts used: variables and constants, arrays, dynamic arrays (`new[]` / `delete[]`, 2D `int**`),
pointers, references, pass by value vs by reference, recursion, `enum class`, conditions and loops.
No `class`, no `struct`: data lives in parallel arrays, logic lives in free functions.

## Project layout

```
include/                 declarations (.h)
  constants.h            business constants (VAT, fees, discounts, limits)
  types.h                enum class types: Category, Size, OrderType, Payment, Tier, MenuOption
  input.h                safe input: readInt, readDouble, readYesNo, readName
  helpers.h              enum -> text, sizeFactor, tierOf, tierDiscountRate
  logic.h                findStock/findPrice (pointers), restock (reference), calcVAT (value), payWithCash
  recursion.h            digitSum, checkDigit
  memory.h               growMenu, addItem, addCustomer, freeCart
  screens.h              showMenu, printMainMenu, changePrice, showCustomers
  order.h                newOrder (cart, pricing pipeline, payment, loyalty, receipt)
  reports.h              closeDay, weeklyReport
src/                     implementations (.cpp), one per header, plus main.cpp
tests/                   input files you can pipe into the program
```

`constants.h` and `types.h` only hold constants and types, so they have no `.cpp` file.

## Build and run

**g++ (Linux, macOS, MinGW on Windows)**
```
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o pos
./pos
```

**make**
```
make          # build
make test     # run the full-day test script
make clean
```

**CMake / Visual Studio / CLion**
```
cmake -S . -B build
cmake --build build
```
In Visual Studio you can also use *File > Open > Folder* and pick this folder (it reads CMakeLists.txt).

## Quick tests

```
./pos < tests/mona_card.txt   # receipt #1001-2, TOTAL 203.17, paid 205.20
./pos < tests/full_day.txt    # two orders, closing report "Drawer SHORT by 21.12", weekly report
```

## Main test case (Mona)

Silver member, dine in, Latte L x2 + Cheesecake x1, pays by card:
subtotal 177.50, combo -10.00, Silver 5% -8.38, service 12% +19.09, VAT 14% +24.95,
total 203.17, card fee +2.03, charged 205.20, receipt #1001-2, 20 points.
