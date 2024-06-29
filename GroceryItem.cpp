
#include "GroceryItem.h"

// Constructor implementation
GroceryItem::GroceryItem(const std::string& itemName) : itemName(itemName), itemQuantity(1) {}

// Constructor implementation with quantity
GroceryItem::GroceryItem(const std::string& itemName, int itemQuantity) : itemName(itemName), itemQuantity(itemQuantity) {}

// Get name of the GroceryItem
std::string GroceryItem::getItemName() const {
    return itemName;
}

// Get quantity of the GroceryItem
int GroceryItem::getItemQuantity() const {
    return itemQuantity;
}

// Increment the quantity
void GroceryItem::incrementItemQuantity() {
    itemQuantity++;
}

// Decrement the quantity
void GroceryItem::decrementItemQuantity() {
    if (itemQuantity > 0) {
        itemQuantity--;
    }
}

// Operator overloading for set operations
bool GroceryItem::operator<(const GroceryItem& other) const {
    return itemName.compare(other.getItemName()) < 0;
}

