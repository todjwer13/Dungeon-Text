#pragma once
#include "Core.h"

class Player
{
public:
    Unit stat;
    int mp = 0;
    int maxMp = 0;
    int gold = 0;
    int currentExp = 0;
    int maxExp = 50;
    int level = 0;
    int weaponAtk = 0;
    int armorHp = 0;
    int armorDef = 0;
    int floor = 1;
    int floorCount = 0;

    std::vector <Item> inventory;

    void AddExperience(int exp);
    void LevelUp();

    void giveStartetPack();

    void refreshStatus();

    void showInventory();

    void showEnding();

    void rest();

    void showPlayerItem();
};

