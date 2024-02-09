#include "Item.h"

Item::Item() {
  targetType = "item";
  animationDuration = 20;
  actionDesc = {
      "Pick an item from your inventory"
    };
}

Item::~Item() {
}

//might need to modify for 
int Item::perform(Unit* user, std::vector<Unit*> targets,  Game& game) {
  return animationDuration;
};