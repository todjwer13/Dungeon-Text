#pragma once
#include <string>
#include <vector>

struct Item {
    std::string name;
    int itemType;
    int weaponAtk = 0;
    int armorDef = 0;
    int hp = 0;
    int armorHp = 0;
    int tier = 0;
    int price = 0;
};

enum ItemCategory {
    CONSUMABLE = 1,
    RELICS = 2
};

struct Unit {
    std::string name = "Unknown";
    int hp = 0;
    int maxHp = 0;
    int atk = 0;
    int def = 0;
    int speed = 0;
    int evasion = 0;
};

struct Monster {
    Unit stat;
    int giveExp = 0;
    int giveGold = 0;
    int variant = 0;
};


Item ItemList(int type);
Monster CreateMonster(int type);