#include "Action/Actions.h"
#include "Combat.h"
#include "Token/Tokens.h"

std::vector<Texture2D> tokenTextures = {};

// loads token textures
void Combat::loadTokenTextures() 
{
  tokenTextures.push_back(loadTexture("Poison"));
  tokenTextures.push_back(loadTexture("AtkBoost"));
  tokenTextures.push_back(loadTexture("DefBoost"));
  tokenTextures.push_back(loadTexture("Warning"));
}

bool Combat::isHero(Unit* unit) {
  Hero* hero = dynamic_cast<Hero*>(unit);
  return hero != nullptr;
}
bool Combat::isFoe(Unit* unit) {
  Foe* foe = dynamic_cast<Foe*>(unit);
  return foe != nullptr;
}

Foe* Combat::createFoe(const std::string& foeId) {
  // add more here
  if (foeId == "FoxFoe") return new FoxFoe();
  if (foeId == "Grape") return new Grape();
  if (foeId == "BlueBerry") return new BlueBerry();
  if (foeId == "WildBerry") return new WildBerry();
  if (foeId == "BerryWizard") return new BerryWizard();
  return nullptr;
}

Action* Combat::createAction(const std::string& actionId, int amount) {
  // add more here
  if (actionId == "DoNothing") return new DoNothing();
  if (actionId == "Strike") return new Strike();
  if (actionId == "Item") return new Item();
  if (actionId == "InflictPoison") return new InflictPoison(amount);
  if (actionId == "BoostAtk") return new BoostAtk(amount);
  if (actionId == "BoostDef") return new BoostDef(amount);
  if (actionId == "Heal") return new Heal(amount);
  if (actionId == "Charge") return new Charge(amount);
  if (actionId == "ChargeStrike") return new ChargeStrike(amount);
  return nullptr;
}

Action* Combat::getItemAction(Inventory combatInventory) {
  if (combatInventory.GetItem(highlightedItem) > 0) {
    const auto& itemProperties = ItemAssets::items.at(highlightedItem);
    switch(itemProperties.type) {
      case ItemType::HEALING:
            targets.push_back(currentUnit);
            selected = 0;
            combatInventory.RemoveItem(highlightedItem);
            return new Heal(itemProperties.value);
      case ItemType::DAMAGE:
            availableTargets = foes;
            numberOfTargets = 1;
            selected = 0;
            combatInventory.RemoveItem(highlightedItem);
            return new Strike(itemProperties.value);
      case ItemType::NEUTRAL:
            currentUnit->actionDialouge += "Not a Valid Item for Combat";
            return nullptr;
    }
  }
  else {
    currentUnit->actionDialouge += "You are out of " + itemList[selected];
    fprintf(stderr, "You are out of %d\n", itemList[selected]);
    return nullptr;
  }
}

Token* Unit::createToken(const std::string& tokenId, int stack) {
  if (tokenId == "Poison") return new Poison(stack, tokenTextures[0]);
  if (tokenId == "AtkBoost") return new AtkBoost(stack, tokenTextures[1]);
  if (tokenId == "DefBoost") return new DefBoost(stack, tokenTextures[2]);
  if (tokenId == "Warning") return new Warning(stack, tokenTextures[3]);
}


std::vector<Unit*> Combat::unitsVanquished(std::vector<Unit*> units) {
  int i = 0;
  std::vector<Unit*> newUnits = {};
  for (Unit* unit : units) {
    if(unit->hp > 0){
      newUnits.push_back(unit);
      // if(isFoe(unit)) {
      //   // add code for the loot/exp the foe holds
      // }
      i++;
    }
  }
  return newUnits;
}