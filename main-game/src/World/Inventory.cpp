#include "Inventory.h"
#include <iostream>

void Inventory::AddItem(const std::string& itemId) {
    items[itemId]++;
}

void Inventory::AddItem(const std::string& itemId, int quantity) {
  if (quantity < 1) fprintf(stderr, "Tried to add non-positive number of items\n");
  else items[itemId] += quantity;
}

void Inventory::RemoveItem(const std::string& itemId) {
  if (items[itemId] <= 0) items[itemId] = 0;
  items[itemId]--;
}

void Inventory::UseItem(const std::string& itemId) {
    auto it = items.find(itemId);
    if (it != items.end() && it->second > 0) {
        const auto& itemProperties = ItemAssets::items.at(itemId);
        switch (itemProperties.type) {
            case ItemType::HEALING:
                std::cout << "Healing with " << itemProperties.id << " for " << itemProperties.value << " HP." << std::endl;
                break;
            case ItemType::DAMAGE:
                std::cout << "Attacking with " << itemProperties.id << " for " << itemProperties.value << " damage." << std::endl;
                break;
            case ItemType::NEUTRAL:
                std::cout << "Using " << itemProperties.id << " which is a neutral item." << std::endl;
                break;
        }
        it->second--;
    } else {
        std::cout << "Item not found in inventory." << std::endl;
    }
}

bool Inventory::hasKey() {
  return (keys > 0);
}

int Inventory::getKeys() {
  return keys;
}

void Inventory::addKeys(int numberOfKeys) {
  if (numberOfKeys < 0) fprintf(stderr, "Error: Tried to add negative number of keys to inventory\n");
  else keys += numberOfKeys;
}

void Inventory::setKeys(int numberOfKeys) {
  if (numberOfKeys < 0) {
    fprintf(stderr, "Error: Tried to set an inventory to have a negative number of keys\n");
    keys = 0;
  }
  else keys = numberOfKeys;
}

void Inventory::removeKey() {
  if (keys < 1) {
    fprintf(stderr, "Error: Tried to remove key from inventory without keys\n");
  }
  else {
    --keys;
  }
}