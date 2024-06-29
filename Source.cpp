#include "GroceryItem.h"

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <stdexcept>
#include "GroceryItem.h"

// Function to read inventory file and return a set of GroceryItems
// @param filename - the name of the file to read from
// @returns - a set of GroceryItems read from the file
std::set<GroceryItem> readInventoryFile(const std::string& filename) {
    std::set<GroceryItem> groceryItems;
    std::ifstream inputFile(filename);
    std::string itemName;

    if (!inputFile) {
        throw std::runtime_error("Error opening file");
    }

    // Read each item name from the file
    while (inputFile >> itemName) {
        GroceryItem newItem(itemName);
        auto existingItem = groceryItems.find(newItem);

        if (existingItem != groceryItems.end()) {
            // If item already exists in the set, create a new item with updated quantity
            GroceryItem updatedItem(existingItem->getItemName(), existingItem->getItemQuantity());
            updatedItem.incrementItemQuantity();
            groceryItems.erase(existingItem);
            groceryItems.insert(updatedItem);
        }
        else {
            newItem.incrementItemQuantity();
            groceryItems.insert(newItem);
        }
    }

    inputFile.close();
    return groceryItems;
}

// Function to backup data to a file
// @param items - the set of GroceryItems to backup
// @param filename - the name of the backup file
void backupInventoryData(const std::set<GroceryItem>& items, const std::string& filename) {
    std::ofstream outputFile(filename);

    if (!outputFile) {
        throw std::runtime_error("Error opening file");
    }

    for (const auto& item : items) {
        outputFile << item.getItemName() << " " << item.getItemQuantity() << std::endl;
    }

    outputFile.close();
}

// Function to display item frequency
// @param items - the set of GroceryItems to display
void displayAllItemFrequencies(const std::set<GroceryItem>& items) {
    for (const auto& item : items) {
        std::cout << item.getItemName() << " " << item.getItemQuantity() << std::endl;
    }
}

// Function to display histogram
// @param items - the set of GroceryItems to display
void displayItemHistogram(const std::set<GroceryItem>& items) {
    for (const auto& item : items) {
        std::cout << item.getItemName() << " ";
        for (int i = 0; i < item.getItemQuantity(); i++) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}

// Function to search for an item's frequency
// @param items - the set of GroceryItems to search
// @param itemName - the name of the item to search for
void searchForItem(const std::set<GroceryItem>& items, const std::string& itemName) {
    for (const auto& item : items) {
        if (item.getItemName() == itemName) {
            std::cout << itemName << " was purchased " << item.getItemQuantity() << " times." << std::endl;
            return;
        }
    }
    std::cout << itemName << " was not found in the inventory." << std::endl;
}

// Function to display the main menu
void displayMenu() {
    std::cout << "1. Search for an item\n";
    std::cout << "2. Display all item frequencies\n";
    std::cout << "3. Print histogram to console\n";
    std::cout << "4. Exit\n";
}

int main() {
    const std::string inputFilename = "inventory.txt"; // Updated input file name
    const std::string backupFilename = "frequency.dat";
    std::set<GroceryItem> groceryItems;

    try {
        groceryItems = readInventoryFile(inputFilename);
        backupInventoryData(groceryItems, backupFilename);
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    int userChoice = 0;
    while (userChoice != 4) {
        displayMenu();
        std::cout << "Enter your choice: ";
        try {
            std::cin >> userChoice;

            if (std::cin.fail()) {
                throw std::invalid_argument("Invalid input. Please enter a number between 1 and 4.");
            }

            std::string itemName;

            switch (userChoice) {
            case 1:
                std::cout << "Enter item name to search: ";
                std::cin >> itemName;
                searchForItem(groceryItems, itemName);
                break;
            case 2:
                displayAllItemFrequencies(groceryItems);
                break;
            case 3:
                displayItemHistogram(groceryItems);
                break;
            case 4:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }

    return 0;
}
