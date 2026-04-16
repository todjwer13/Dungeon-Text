// encoding: UTF-8
#include "Player.h"
#include "GameSystem.h"
#include <iostream>
#include <algorithm>

void Player::AddExperience(int exp) {
    currentExp += exp;
    std::cout << "Gained " << exp << " EXP!\n";

    while (currentExp >= maxExp) {
        LevelUp();
    }
}

void Player::LevelUp() {
    system("cls");
    currentExp -= maxExp;
    level++;
    std::cout << "Level up! Current level: " << level << "\n";
    maxExp = static_cast<int>(maxExp * 1.2);

    stat.maxHp += 20;
    std::cout << "Max HP increased by 20.\n";
    stat.hp = stat.maxHp + armorHp;
    std::cout << "HP has been restored.\n";
    stat.atk += 5;
    std::cout << "Attack increased by 5.\n";
    stat.def += 2;
    std::cout << "Defense increased by 2.\n";
}

void Player::giveStartetPack() {
    for (int i = 1; i <= 3; i++) {
        inventory.push_back(ItemList(1));
    }
    inventory.push_back(ItemList(4));
}

void Player::refreshStatus() {
    // Reset relic bonuses
    weaponAtk = 0;
    armorDef = 0;
    armorHp = 0;
    // Apply relic bonuses from inventory
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i].itemType == RELICS)
        {
            weaponAtk += inventory[i].weaponAtk;
            armorDef += inventory[i].armorDef;
            armorHp += inventory[i].armorHp;
        }
    }
}

void Player::showInventory() {
    int inventoryInput = 0;
    int throwAwayInput = 0;
    std::vector<int> consumableIndices;

    std::cout << "Acquired relic items:" << std::endl;
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i].itemType == RELICS)
        {
            std::cout << "\n" << inventory[i].name;
            if (inventory[i].weaponAtk > 0) {
                std::cout << " | +ATK: " << inventory[i].weaponAtk;
            }
            if (inventory[i].armorDef > 0) {
                std::cout << " | +DEF: " << inventory[i].armorDef;
            }
            if (inventory[i].armorHp > 0) {
                std::cout << " | +HP: " << inventory[i].armorHp;
            }
        }
    }

    std::cout << "\n------------------------------" << std::endl;
    std::cout << "\nConsumable items:" << std::endl;
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i].itemType == CONSUMABLE)
        {
            consumableIndices.push_back(i);
            std::cout << i + 1 << ". " << inventory[i].name << " | Heal: " << inventory[i].hp << std::endl;
        }
    }

    if (consumableIndices.empty()) {
        std::cout << "(No usable items.)" << std::endl;
    }

    std::cout << "\n0. Go back" << std::endl;
    std::cout << "\nEnter number: ";
    std::cin >> inventoryInput;

    if (inventoryInput == 0) {
        return;
    }

    if (inventoryInput > consumableIndices.size()) {
        std::cout << "\nInvalid input." << std::endl;
        system("pause");
        return;
    }

    // Use item logic
    int targetIdx = consumableIndices[inventoryInput - 1]; // actual inventory index
    Item& selectedItem = inventory[targetIdx];

    std::cout << "\n[Item " << inventoryInput << ": " << selectedItem.name << "] used!" << std::endl;

    int healAmount = selectedItem.hp;
    stat.hp = std::min(stat.hp + healAmount, stat.maxHp + armorHp);

    inventory.erase(inventory.begin() + targetIdx);

    system("pause");

    if (inventoryInput > inventory.size()) {
        std::cout << "\nInvalid input." << std::endl;
        return;
    }
}

void Player::showEnding() {
    system("cls");
    std::cout << "Congratulations! You defeated the boss!" << std::endl;
    std::cout << "\nYou finally reached the top of the dungeon and defeated the boss." << std::endl;

    std::cout << "\n[ Final Record ]" << std::endl;
    std::cout << "- Name: " << stat.name << std::endl;
    std::cout << "- Final Level: " << level << std::endl;
    std::cout << "- Collected Gold: " << gold << " Gold" << std::endl;

    std::cout << "\n[ Legendary relics acquired ]" << std::endl;
    for (const auto& item : inventory) {
        if (item.itemType == RELICS) {
            std::cout << "- " << item.name << std::endl;
        }
    }

    std::cout << "\nThanks for playing!" << std::endl;
    std::cout << "Press any key to return to the main screen." << std::endl;

    // Reset character
    stat.name = "Unknown";

    system("pause");
    return;
}

void Player::showPlayerItem() {
    for (size_t i = 0; i < inventory.size(); i++) {
        std::cout << "\n" << (i + 1) << ". " << inventory[i].name;
    }
}

void Player::rest() {
    std::cout << "\nResting..." << std::endl;
    gold -= 100; // rest cost
    stat.hp = stat.maxHp + armorHp;
    std::cout << "\nHP fully restored!" << std::endl;
    system("pause");
}




