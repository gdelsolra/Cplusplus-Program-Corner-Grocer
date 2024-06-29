
#pragma once
#include <string>

class GroceryItem {
public:
    // Constructor to initialize the GroceryItem with a name and default quantity
    // @param itemName - the name of the grocery item
    GroceryItem(const std::string& itemName);

    // Constructor to initialize the GroceryItem with a name and specific quantity
    // @param itemName - the name of the grocery item
    // @param itemQuantity - the quantity of the grocery item
    GroceryItem(const std::string& itemName, int itemQuantity);

    // Get the name of the GroceryItem
    // @returns - the name of the grocery item
    std::string getItemName() const;

    // Get the quantity of the GroceryItem
    // @returns - the quantity of the grocery item
    int getItemQuantity() const;

    // Increment the quantity of the GroceryItem
    void incrementItemQuantity();

    // Decrement the quantity of the GroceryItem
    void decrementItemQuantity();

    // Operator overloading for set operations
    // @param other - another GroceryItem to compare with
    // @returns - true if this item's name is less than the other item's name
    bool operator<(const GroceryItem& other) const;

private:
    std::string itemName;
    int itemQuantity;
};



