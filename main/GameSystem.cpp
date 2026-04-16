#include "GameSystem.h"
#include <iostream>
#include <vector>
#include <algorithm>


void GameSystem::startMenu(std::vector<Player>& saveSlots, int& characterCount)
{
    while (true) {
        system("cls");
        cleanUpCharacters(saveSlots, characterCount);
        int menuInput = 0;
        std::cout << "Welcome to the game!" << std::endl;
        std::cout << "\n1. Start Game" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::cout << "\nInput: ";
        std::cin >> menuInput;
        if (menuInput == 1)
        {
            system("cls");
            characterMenu(saveSlots, characterCount);
        }
        else if (menuInput == 2)
        {
            system("cls");
            std::cout << "\nExiting game.";

            exit(0);
        }
        else
        {
            std::cout << "\nInvalid input.";
            system("pause");
        }
    }

}

void GameSystem::gameLoop(Player& player, int& characterCount)
{
    std::vector<Item> shopStock;
    randomItemList(player, shopStock);
    int playingInput = 0;
    char restInput;
    while (true) {
        player.refreshStatus();
        system("cls");
        std::cout << "Name: " << player.stat.name << "   |   " << "Gold: " << player.gold << "    |   " << "Floor: " << player.floor << std::endl;
        std::cout << "\nLevel: " << player.level << "   |   " << "EXP: " << player.currentExp << std::endl;
        std::cout << "\nHP: " << player.stat.hp << "/" << player.stat.maxHp + player.armorHp << std::endl;
        std::cout << "\nATK: " << player.stat.atk + player.weaponAtk << "   |   " << "DEF: " << player.stat.def + player.armorDef << std::endl;

        std::cout << "\nChoose an action." << std::endl;
        std::cout << "\n1. Talk   2. Explore     3. Go up a floor     4. Rest     5. Open Bag    6. Save and Exit" << std::endl;
        std::cout << "\nInput: ";
        std::cin >> playingInput;
        if (playingInput == 1)
        {
            showShop(player, shopStock);
        }
        else if (playingInput == 2)
        {
            system("cls");
            std::cout << "\nYou chose to explore." << std::endl;
            std::cout << "\nSearching for enemies..." << std::endl;
            if (player.floor == 10) {
                Monster bossMonster = CreateMonster(4);
                std::cout << "\nBoss monster [" << bossMonster.stat.name << "] has appeared!" << std::endl;
                bool isVictory = startBattle(player, bossMonster);
                if (isVictory && bossMonster.variant == 2) { // assume 2 is boss
                    if (player.floor == 10) {
                        player.showEnding(); // call ending
                        return; // exit game loop to main menu
                    }
                }
                if (!isVictory)
                {
                    player.stat.name = "Unknown";
                    std::cout << "\nCharacter was destroyed. Returning to main menu." << std::endl;
                    system("pause");
                    return;
                }
            }
            else {
                int randomType = (rand() % 3) + 1;
                Monster currentMonster = CreateMonster(randomType);

                std::cout << "\nOh! [" << currentMonster.stat.name << "] has appeared!" << std::endl;

                std::cout << "\n 1. Fight   2. Run" << std::endl;
                std::cout << "\nInput: ";
                std::cin >> playingInput;
                if (playingInput == 1) {

                    bool isVictory = startBattle(player, currentMonster);

                    if (!isVictory)
                    {
                        player.stat.name = "Unknown";

                        std::cout << "\nCharacter was destroyed. Returning to main menu." << std::endl;
                        system("pause");
                        return;
                    }
                }
                else if (playingInput == 2) {
                    std::cout << "\nYou chose to run away." << std::endl;
                }
            }
        }
        else if (playingInput == 3)
        {
            system("cls");
            std::cout << "\nYou chose to go up a floor." << std::endl;
            floorTransition(player);
            shopStock.clear();
            randomItemList(player, shopStock);
        }
        else if (playingInput == 4)
        {
            system("cls");
            std::cout << "\nYou chose to rest." << std::endl;
            std::cout << "\nResting fully recovers HP but costs 100 gold." << std::endl;
            std::cout << "\nDo you want to rest? (y/n): ";
            std::cin >> restInput;
            if (restInput == 'y' || restInput == 'Y') {
                if (player.gold >= 100) {
                    player.rest();
                }
            }
            else if (restInput == 'n' || restInput == 'N') {
                std::cout << "\nYou chose not to rest." << std::endl;
            }
            else {
                std::cout << "\nInvalid input. No rest taken." << std::endl;
            }
        }
        else if (playingInput == 5)
        {
            system("cls");
            std::cout << "\nOpening bag." << std::endl;
            player.showInventory();
        }
        else if (playingInput == 6)
        {
            system("cls");
            std::cout << "\nSaving and exiting." << std::endl;
            return;
        }
        else
        {
            std::cout << "\nInvalid input." << std::endl;
        }
    }
}



void GameSystem::showMerchantTalk()
{
    std::vector<std::string> talks = {
        "What a fine day! Need anything?",
        "There are strange rumors about this floor, be careful.",
        "Recently a strong monster is said to appear on this floor. Be careful!",
        "They say there's a hidden treasure on this floor. Want to try looking for it?",
        "Adventurers are increasing, so good gear is harder to find now.",
        "Here to buy? If you have something good I'll consider buying it!",
        "Sometimes it's good to stretch your legs."
    };
    int randomIndex = rand() % talks.size();
    std::cout << talks[randomIndex] << std::endl;
}

bool GameSystem::startBattle(Player& player, Monster& monster)
{
    while (player.stat.hp > 0 && monster.stat.hp > 0)
    {
        system("pause");
        if (player.stat.speed >= monster.stat.speed)
        {
            int damageToMonster = std::max(0, (player.stat.atk + player.weaponAtk) - monster.stat.def);
            monster.stat.hp -= damageToMonster;
            std::cout << "Player dealt " << damageToMonster << " damage! Monster HP: " << monster.stat.hp << "/" << monster.stat.maxHp << std::endl;
            if (monster.stat.hp <= 0)
            {
                std::cout << "Monster defeated!" << std::endl;
                player.AddExperience(monster.giveExp);
                player.gold += monster.giveGold;
                std::cout << "Gained " << monster.giveGold << " gold! Current gold: " << player.gold << std::endl;
                if (monster.variant == 1) {
                    player.floorCount++;
                    std::cout << "You can advance to the next floor!" << std::endl;
                }
                system("pause");
                return true;
            }
            int damageToPlayer = std::max(0, monster.stat.atk - (player.stat.def + player.armorDef));
            player.stat.hp -= damageToPlayer;
            std::cout << "Monster dealt " << damageToPlayer << " damage! Player HP: " << player.stat.hp << "/" << player.stat.maxHp << std::endl;
            if (player.stat.hp <= 0)
            {
                std::cout << "Player was defeated..." << std::endl;
                system("pause");
                return false;
            }
        }
        else
        {
            int damageToPlayer = std::max(0, monster.stat.atk - player.stat.def);
            player.stat.hp -= damageToPlayer;
            std::cout << "Monster dealt " << damageToPlayer << " damage! Player HP: " << player.stat.hp << "/" << player.stat.maxHp << std::endl;
            if (player.stat.hp <= 0)
            {
                std::cout << "Player was defeated..." << std::endl;
                system("pause");
                return false;
            }
            int damageToMonster = std::max(0, player.stat.atk - monster.stat.def);
            monster.stat.hp -= damageToMonster;
            std::cout << "Player dealt " << damageToMonster << " damage! Monster HP: " << monster.stat.hp << "/" << monster.stat.maxHp << std::endl;
            if (monster.stat.hp <= 0)
            {
                std::cout << "Monster defeated!" << std::endl;
                player.AddExperience(monster.giveExp);
                player.inventory.push_back(ItemList(5));
                player.gold += monster.giveGold;
                std::cout << "Gained " << monster.giveGold << " gold! Current gold: " << player.gold << std::endl;
                if (monster.variant == 1) {
                    player.floorCount++;
                    std::cout << "You can advance to the next floor!" << std::endl;
                }
                system("pause");
                return true;
            }
        }
    }
    return false;
}

void GameSystem::floorTransition(Player& player) {
    if (player.floorCount >= 1) {
        player.floor++;
        player.floorCount = 0;
        std::cout << "Moving to the next floor." << std::endl;
        system("pause");
    }
    else {
        std::cout << "You cannot move to the next floor yet." << std::endl;
        system("pause");
    }
}

void GameSystem::randomItemList(Player& player, std::vector<Item>& shopStock) {
    // generate shop stock per floor

    int floor = player.floor;
    shopStock.push_back(ItemList(1));
    std::cout << "\n" << "1. " << shopStock[0].name << " | Price: " << shopStock[0].price;
    for (int i = 1; i <= 4; i++)
    {
        int randomCnt = rand() % 100;
        int pickedItem = (floor * 3) + randomCnt;

        if (pickedItem < 90) {
            int randomType = (rand() % 3 + 1);
            Item itemList = ItemList(randomType);
            shopStock.push_back(itemList);
            std::cout << "\n" << (i + 1) << ". " << shopStock[i].name << " | Price: " << shopStock[i].price;
        }
        else {
            int randomType = (rand() % 7 + 1);
            Item itemList = ItemList(randomType);
            shopStock.push_back(itemList);
            std::cout << "\n" << (i + 1) << ". " << shopStock[i].name << " | Price: " << shopStock[i].price;
        }
    }
}

void GameSystem::showShopItem(Player& player, std::vector<Item>& shopStock) {
    // print items
    for (int i = 0; i <= shopStock.size() - 1; i++) {
        printf("\n %d. %s | Price: %d\n", i + 1, shopStock[i].name.c_str(), shopStock[i].price);
    }
}

void GameSystem::showShop(Player& player, std::vector<Item>& shopStock)
{
    while (true)
    {

        system("cls");
        int conCount = 0;
        int shopInput = 0;
        int buyInput = 0;
        int sellInput = 0;

        for (int i = 0; i < player.inventory.size(); i++) {
            if (player.inventory[i].itemType == CONSUMABLE)
            {
                conCount++;
            }
        }

        std::cout << "\nYou started a conversation." << std::endl;
        std::cout << "\nMerchant" << std::endl;
        showMerchantTalk();
        std::cout << "\n1. Buy   2. Sell     3. Go back" << std::endl;
        std::cout << "\nInput: ";
        std::cin >> shopInput;
        if (shopInput == 1)
        {
            std::cout << "\nBuy selected." << std::endl;
            system("cls");
            if (conCount >= 3)
            {
                std::cout << "\nConsumable items full!!" << std::endl;
            }
            std::cout << "\nAvailable items" << std::endl;
            std::cout << "\n 0. Go back" << std::endl;
            showShopItem(player, shopStock);
            std::cout << "\n------------------------------" << std::endl;
            std::cout << "\nCurrent gold: " << player.gold << std::endl;
            std::cout << "\nEnter item number: ";
            std::cin >> buyInput;
            // buying logic
            if (buyInput == 0) {
                std::cout << "\nReturning." << std::endl;
                break;
            }

            if (buyInput < 1 || buyInput > shopStock.size()) {
                std::cout << "\nInvalid input." << std::endl;
            }
            else {
                if (shopStock[buyInput - 1].itemType == CONSUMABLE && conCount >= 3)
                {
                    std::cout << "\nYou can hold up to 3 consumables." << std::endl;
                    system("pause");
                    return;
                }

                Item selectedItem = shopStock[buyInput - 1];
                if (player.gold >= selectedItem.price) {
                    player.gold -= selectedItem.price;
                    player.inventory.push_back(selectedItem);
                    shopStock.erase(shopStock.begin() + (buyInput - 1));
                    std::cout << "\n" << selectedItem.name << " purchased! Remaining gold: " << player.gold << std::endl;
                    system("pause");
                }
                else {
                    std::cout << "\nNot enough gold." << std::endl;
                    system("pause");

                }
            }
        }
        else if (shopInput == 2)
        {
            std::cout << "\nSell selected." << std::endl;
            system("cls");
            std::cout << "\nItems to sell" << std::endl;
            std::cout << "\n Current gold: " << player.gold << std::endl;
            std::cout << "\n 0. Go back" << std::endl;
            player.showPlayerItem();
            std::cout << "\nEnter item number to sell: ";
            std::cin >> sellInput;
            // selling logic
            if (sellInput == 0) {
                std::cout << "\nReturning." << std::endl;
                break;
            }

            if (sellInput < 1 || sellInput > player.inventory.size()) {
                std::cout << "\nInvalid input." << std::endl;
            }
            else {
                Item selectedItem = player.inventory[sellInput - 1];
                player.gold += selectedItem.price * 0.5;
                player.inventory.erase(player.inventory.begin() + (sellInput - 1));
                std::cout << "\n" << selectedItem.name << " sold! Current gold: " << player.gold << std::endl;
                system("pause");
            }
        }
        else if (shopInput == 3)
        {
            std::cout << "\nReturning." << std::endl;
            break;
        }
        else
        {
            std::cout << "\nInvalid input." << std::endl;
        }
    }
}


// global wrapper functions to match declarations in Core.h
Item ItemList(int type) {
    GameSystem gs;
    return gs.ItemList(type);
}

Monster CreateMonster(int type) {
    GameSystem gs;
    return gs.CreateMonster(type);
}

Item GameSystem::ItemList(int type) {
    Item newItem;
    switch (type) {
    case 1:
        newItem.name = "Small Health Potion";
        newItem.hp = 50;
        newItem.price = 50;
        newItem.itemType = CONSUMABLE;
        newItem.tier = 1;
        break;
    case 2:
        newItem.name = "Medium Health Potion";
        newItem.hp = 150;
        newItem.price = 130;
        newItem.itemType = CONSUMABLE;
        newItem.tier = 2;
        break;
    case 3:
        newItem.name = "Large Health Potion";
        newItem.hp = 300;
        newItem.price = 250;
        newItem.itemType = CONSUMABLE;
        newItem.tier = 3;
        break;
    case 4:
        newItem.name = "Sword";
        newItem.weaponAtk = 10;
        newItem.price = 800;
        newItem.itemType = RELICS;
        newItem.tier = 1;
        break;
    case 5:
        newItem.name = "Armor";
        newItem.armorHp = 50;
        newItem.armorDef = 10;
        newItem.price = 1000;
        newItem.itemType = RELICS;
        newItem.tier = 1;
        break;
    case 6:
        newItem.name = "Boots";
        newItem.armorHp = 20;
        newItem.armorDef = 5;
        newItem.price = 700;
        newItem.itemType = RELICS;
        newItem.tier = 1;
        break;
    case 7:
        newItem.name = "Gloves";
        newItem.armorHp = 10;
        newItem.armorDef = 3;
        newItem.price = 500;
        newItem.itemType = RELICS;
        newItem.tier = 1;
        break;
    }
    
    return newItem;
}

// create monster
Monster GameSystem::CreateMonster(int type) {
    Monster newMonster;

    switch (type) {
    case 1:
        newMonster.stat = { "Slime", 30, 30, 6, 2, 5, 0 }; // name, HP, MaxHP, ATK, DEF, SPD, EVA
        newMonster.giveExp = 10;
        newMonster.giveGold = 20;
        newMonster.variant = 0;
        break;
    case 2:
        newMonster.stat = { "Goblin", 50, 50, 12, 5, 8, 0 };
        newMonster.giveExp = 25;
        newMonster.giveGold = 50;
        newMonster.variant = 0;
        break;
    case 3:
        newMonster.stat = { "Orc", 100, 100, 20, 15, 4, 0 };
        newMonster.giveExp = 60;
        newMonster.giveGold = 150;
        newMonster.variant = 1;
        break;
    case 4:
        newMonster.stat = { "Dragon", 15, 15, 13, 10, 10, 0 };
        newMonster.giveExp = 0;
        newMonster.giveGold = 0;
        newMonster.variant = 2;
        break;
    }
    return newMonster;
}

void GameSystem::characterMenu(std::vector<Player>& saveSlots, int& characterCount)
{
    while (true) {
        if (characterCount == 0) {
            system("cls");
            std::cout << "[!] No created characters." << std::endl;
            createCharacter(saveSlots, characterCount);
        }

        else {
            system("cls");
            std::cout << "Select Character" << std::endl;
            for (int i = 0; i < characterCount; i++) {
                std::cout << i + 1 << ". " << saveSlots[i].stat.name << " (Lv." << saveSlots[i].level << ")" << std::endl;
            }
            std::cout << "5. Create Character" << std::endl;
            std::cout << "6. Delete Character" << std::endl;
            std::cout << "0. Exit" << std::endl;
            std::cout << "Choice: ";

            int select = 0;
            std::cin >> select;

            if (select == 0) return;

            if (select > 0 && select <= characterCount) {
                system("cls");
                int targetIndex = select - 1;

                std::cout << "[" << saveSlots[targetIndex].stat.name << "] character selected!" << std::endl;
                GameSystem game;
                game.gameLoop(saveSlots[targetIndex], characterCount);


                break;
            }
            else if (select == 5) {
                if (characterCount >= 3) {
                    system("cls");
                    std::cout << "Character slots are full!" << std::endl;
                    system("pause");
                }
                else {
                    system("cls");
                    createCharacter(saveSlots, characterCount);
                }
            }
            else if (select == 6) {
                system("cls");
                deleteCharacter(saveSlots, characterCount);
            }
            else {
                std::cout << "\nInvalid number. Please choose again." << std::endl;
            }
        }
    }
}

void GameSystem::cleanUpCharacters(std::vector<Player>& saveSlots, int& characterCount) {
    for (int i = 0; i < saveSlots.size(); i++) {
        if (saveSlots[i].stat.name == "Unknown") {
            saveSlots[i].inventory.clear();
            saveSlots.erase(saveSlots.begin() + i);
            characterCount--;
        }
    }
}



void GameSystem::createCharacter(std::vector<Player>& saveSlots, int& characterCount) {
    if (characterCount >= 3) {
        system("cls");
        std::cout << "Character slots are full!" << std::endl;
        return;
    }

    Player newPlayer;
    std::cout << "Name: ";
    std::string newName;
    std::cin >> newName;


    newPlayer.stat.name = newName;
    newPlayer.stat.hp = 100;
    newPlayer.stat.maxHp = 100;
    newPlayer.stat.atk = 15;
    newPlayer.stat.def = 5;
    newPlayer.stat.speed = 10;
    newPlayer.stat.evasion = 5;
    newPlayer.gold = 500;
    newPlayer.level = 1;

    newPlayer.giveStartetPack(); // provide starter items
    saveSlots.push_back(newPlayer); // add to vector

    characterCount++;
    system("cls");
    std::cout << "Character [" << newName << "] created!" << std::endl;
    system("pause");
    return;
}

void GameSystem::deleteCharacter(std::vector<Player>& saveSlots, int& characterCount) {
    if (characterCount <= 0) {
        system("cls");
        std::cout << "No characters to delete!" << std::endl;
        return;
    }
    std::cout << "Enter the character number to delete: ";
    int deleteInput = 0;
    std::cin >> deleteInput;
    if (deleteInput < 1 || deleteInput > characterCount) {
        std::cout << "Invalid number!" << std::endl;
        return;
    }
    saveSlots[deleteInput - 1].inventory.clear();
    saveSlots.erase(saveSlots.begin() + deleteInput - 1);
    characterCount--;
    system("cls");
    std::cout << "Character deleted!" << std::endl;
    system("pause");
}