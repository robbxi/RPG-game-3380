#ifndef INVENTORY_H
#define INVENTORY_H

#include "ItemAssets.h"  // Updated to include the correct header file for ItemAssets
#include <string>
#include <unordered_map>

// Inventory class to manage items and quantities
class Inventory {
private:
    std::unordered_map<std::string, int> items; // Map of item IDs to quantities
    int keys = 0;

public:
    void AddItem(const std::string& itemId);
    void AddItem(const std::string& itemId, int quantity);
    void RemoveItem(const std::string& itemId);
    void UseItem(const std::string& itemId);

    // Keys
    bool hasKey();
    int getKeys();
    void addKeys(int numberOfKeys);
    void setKeys(int numberOfKeys);
    void removeKey();


    const std::unordered_map<std::string, int>& GetItems() const {
        return items;
    }
    const int GetItem(std::string i) {
        return items[i];
    }
};

#endif // INVENTORY_H
