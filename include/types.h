// types.h
// Every "pick one of these" choice in the business, as enum class types.
#ifndef TYPES_H
#define TYPES_H

enum class Category  { Drink, Food, Dessert };
enum class Size      { Small, Medium, Large };
enum class OrderType { DineIn, Takeaway, Delivery };
enum class Payment   { Cash, Card, Wallet };
enum class Tier      { Regular, Silver, Gold };
enum class MenuOption { Exit = 0, ShowMenu, NewOrder, AddItem, Restock,
                        ChangePrice, AddCustomer, ShowCustomers,
                        CloseDay, WeeklyReport };

#endif // TYPES_H
