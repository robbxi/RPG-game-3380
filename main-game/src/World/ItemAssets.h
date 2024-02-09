#ifndef ITEM_ASSETS_H
#define ITEM_ASSETS_H

#include <string>
#include <unordered_map>

// Enum for item types
enum class ItemType {
    HEALING,
    DAMAGE,
    NEUTRAL
};

// Struct to define item properties
struct ItemProperties {
    std::string id;
    ItemType type;
    int value; // Healing amount or damage value, 0 for neutral items

    ItemProperties() : type(ItemType::NEUTRAL), value(0) {}

    // Constructor
    ItemProperties(std::string i, ItemType t, int v);

    
};

// ItemAssets class to store all item properties
class ItemAssets {
public:
    static std::unordered_map<std::string, ItemProperties> items;
    static void Initialize();
};

#endif // ITEM_ASSETS_H
