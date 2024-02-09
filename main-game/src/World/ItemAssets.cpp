#include "ItemAssets.h"

// Define ItemProperties constructor
ItemProperties::ItemProperties(std::string i, ItemType t, int v) : id(std::move(i)), type(t), value(v) {}


// Initialize static member of ItemAssets
std::unordered_map<std::string, ItemProperties> ItemAssets::items;

void ItemAssets::Initialize() {
    items["bronze_sword"] = ItemProperties("bronze_sword", ItemType::DAMAGE, 15);
    items["healing_potion"] = ItemProperties("healing_potion", ItemType::HEALING, 25);
    items["stick"] = ItemProperties("stick", ItemType::DAMAGE, 10);
    //items["rock"] = ItemProperties("rock", ItemType::DAMAGE, 8);
    // ... add more items with their properties
}