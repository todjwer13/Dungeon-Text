#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>



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

Item ItemList(int type) {
    Item newItem;
    switch (type) {
    case 1:
        newItem.name = "소형 체력 회복 물약";
        newItem.hp = 50;
        newItem.price = 50;
		newItem.itemType = CONSUMABLE;
        newItem.tier = 1;
        break;
    case 2:
        newItem.name = "중형 체력 회복 물약";
        newItem.hp = 150;
        newItem.price = 130;
        newItem.itemType = CONSUMABLE;
        newItem.tier = 2;
        break;
    case 3:
        newItem.name = "대형 체력 회복 물약";
        newItem.hp = 300;
        newItem.price = 250;
		newItem.itemType = CONSUMABLE;
        newItem.tier = 3;
        break;
    case 4:
        newItem.name = "검";
        newItem.weaponAtk = 10;
        newItem.price = 800;
        newItem.itemType = RELICS;
        newItem.tier = 1;
        break;
    case 5:
        newItem.name = "갑옷";
        newItem.armorHp = 50;
        newItem.armorDef = 10;
        newItem.price = 1000;
        newItem.itemType = RELICS;
        newItem.tier = 1;
        break;
    case 6:
        newItem.name = "신발";
        newItem.armorHp = 20;
        newItem.armorDef = 5;
        newItem.price = 700;
        newItem.itemType = RELICS;
        newItem.tier = 1;
        break;
    case 7:
        newItem.name = "장갑";
        newItem.armorHp = 10;
        newItem.armorDef = 3;
        newItem.price = 500;
        newItem.itemType = RELICS;
        newItem.tier = 1;
        break;
    }

    return newItem;
}

struct Player {
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


    void AddExperience(int exp) {
        currentExp += exp;
        std::cout << exp << "의 경험치를 획득했습니다!\n";

        while (currentExp >= maxExp) {
            LevelUp();
        }
    }

    void LevelUp() {
        system("cls");
        currentExp -= maxExp;
        level++;
        std::cout << "★ 레벨 업! 현재 레벨: " << level << " ★\n";
        maxExp = static_cast<int>(maxExp * 1.2);

        stat.maxHp += 20;
        std::cout << "★ 최대 체력이 올랐습니다 20만큼 증가했습니다" << " ★\n";
        stat.hp = stat.maxHp + armorHp;
        std::cout << "★ 체력이 회복되었습니다. ★\n";
        stat.atk += 5;
        std::cout << "★ 공격력이 5만큼 증가하였습니다. ★\n";
        stat.def += 2;
        std::cout << "★ 방어력이 2만큼 증가하였습니다. ★\n";
    }
};

// 몬스터를 생성해주는 함수
Monster CreateMonster(int type) {
    Monster newMonster;

    switch (type) {
    case 1:
        newMonster.stat = { "슬라임", 30, 30, 6, 2, 5, 0 }; // 이름, HP, MaxHP, ATK, DEF, SPD, EVA
        newMonster.giveExp = 10;
        newMonster.giveGold = 20;
        newMonster.variant = 0;
        break;
    case 2:
        newMonster.stat = { "고블린", 50, 50, 12, 5, 8, 0 };
        newMonster.giveExp = 25;
        newMonster.giveGold = 50;
        newMonster.variant = 0;
        break;
    case 3:
        newMonster.stat = { "오크", 100, 100, 20, 15, 4, 0 };
        newMonster.giveExp = 60;
        newMonster.giveGold = 150;
        newMonster.variant = 1;
        break;
    case 4:
        newMonster.stat = { "드래곤", 15, 15, 13, 10, 10, 0 };
        newMonster.giveExp = 0;
        newMonster.giveGold = 0;
        newMonster.variant = 2;
		break;
    }
    return newMonster;
}




void characterMenu(std::vector<Player>& saveSlots, int& characterCount);
void rest(Player& player);
void cleanUpCharacters(std::vector<Player>& saveSlots, int& characterCount);
void createCharacter(std::vector<Player>& saveSlots, int& characterCount);
void refreshStatus(Player& player);
void giveStartetPack(Player& player);
void showInventory(Player& player);
void gameLoop(Player& player, int& characterCount);
bool startBattle(Player& player, Monster& monster);
Monster CreateMonster(int type);
void showShop(Player& player, std::vector<Item>& shopStock);
void showShopItem(Player& player, std::vector<Item>& shopStock);
void ramdomItemList(Player& player, std::vector<Item>& shopStock);
void showPlayerItem(Player& player);
void showMerchantTalk();
void deleteCharacter(std::vector<Player>& saveSlots, int& characterCount);
void showEnding(Player& player);
void floorTransition(Player& player);

static void startMenu(std::vector<Player>& saveSlots, int& characterCount)
{
    while(true) {
        system("cls");
        cleanUpCharacters(saveSlots, characterCount);
        int menuInput = 0;
        std::cout << "게임에 오신 것을 환영합니다!" << std::endl;
        std::cout << "\n1. 게임 시작하기" << std::endl;
        std::cout << "2. 게임 종료하기" << std::endl;
        std::cout << "\n입력: ";
        std::cin >> menuInput;
        if (menuInput == 1)
        {
            system("cls");
            characterMenu(saveSlots, characterCount);
        }
        else if (menuInput == 2)
        {
            system("cls");
            std::cout << "\n게임을 종료합니다.";

            exit(0);
        }
        else
        {
            std::cout << "\n잘못된 입력입니다.";
			system("pause");
        }
    }
}

void cleanUpCharacters(std::vector<Player>& saveSlots, int& characterCount) {
    for (int i = 0; i < saveSlots.size(); i++) {
        if (saveSlots[i].stat.name == "Unknown") {
            saveSlots[i].inventory.clear();
            saveSlots.erase(saveSlots.begin() + i);
            characterCount--;
        }
    }
}


void characterMenu(std::vector<Player>& saveSlots, int& characterCount)
{
    while (true) {
        if (characterCount == 0) {
            system("cls");
            std::cout << "[!] 생성된 캐릭터가 없습니다." << std::endl;
            createCharacter(saveSlots, characterCount);
        }
        else {
            system("cls");
            std::cout << "캐릭터 선택" << std::endl;
            for (int i = 0; i < characterCount; i++) {
                std::cout << i + 1 << ". " << saveSlots[i].stat.name << " (Lv." << saveSlots[i].level << ")" << std::endl;
            }
            std::cout << "5. 캐릭터 생성하기" << std::endl;
            std::cout << "6. 캐릭터 삭제하기" << std::endl;
            std::cout << "0. 종료하기" << std::endl;
            std::cout << "선택: ";

            int select = 0;
            std::cin >> select;

            if (select == 0) return;

            if (select > 0 && select <= characterCount) {
                system("cls");
                int targetIndex = select - 1;

                std::cout << "[" << saveSlots[targetIndex].stat.name << "] 캐릭터를 선택했습니다!" << std::endl;

                gameLoop(saveSlots[targetIndex], characterCount);


                break;
            }
            else if (select == 5) {
                if (characterCount >= 3) {
                    system("cls");
                    std::cout << "캐릭 슬롯이 가득 찼습니다!" << std::endl;
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
                std::cout << "\n잘못된 번호입니다. 다시 선택해주세요." << std::endl;
            }
        }
    }
}

void createCharacter(std::vector<Player>& saveSlots, int& characterCount) {
    if (characterCount >= 3) {
        system("cls");
        std::cout << "캐릭 슬롯이 가득 찼습니다!" << std::endl;
        return;
    }

    Player newPlayer;
    std::cout << "이름: ";
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

    giveStartetPack(newPlayer); // 아이템 먼저 지급
    saveSlots.push_back(newPlayer); // 벡터에 추가

    characterCount++;
    system("cls");
    std::cout << "캐릭터 [" << newName << "] (이)가 생성되었습니다!" << std::endl;
    system("pause");
    return;
}

void deleteCharacter(std::vector<Player>& saveSlots, int& characterCount) {
    if (characterCount <= 0) {
		system("cls");
		std::cout << "삭제할 캐릭터가 없습니다!" << std::endl;
        return;
    }
	std::cout << "삭제할 캐릭터 번호를 입력하세요: ";
	int deleteInput = 0;
	std::cin >> deleteInput;
    if (deleteInput < 1 || deleteInput > characterCount) {
        std::cout << "잘못된 번호입니다!" << std::endl;
        return;
    }
    saveSlots[deleteInput - 1].inventory.clear();
    saveSlots.erase(saveSlots.begin() + deleteInput - 1);
    characterCount--;
    system("cls");
    std::cout << "캐릭터가 삭제되었습니다!" << std::endl;
    system("pause");
}

void giveStartetPack(Player& player) {
    for (int i = 1; i <= 3; i++) {
        player.inventory.push_back(ItemList(1));
	}
    player.inventory.push_back(ItemList(4));
}

void refreshStatus(Player& player) {
	// 유물 공격력과 방어력, 체력 초기화
    player.weaponAtk = 0;
    player.armorDef = 0;
    player.armorHp = 0;
	// 인벤토리를 순회하면서 유물의 공격력과 방어력, 체력 보너스를 적용
    for (int i = 0; i < player.inventory.size(); i++) {
        if (player.inventory[i].itemType == RELICS)
        {
			player.weaponAtk += player.inventory[i].weaponAtk;
			player.armorDef += player.inventory[i].armorDef;
			player.armorHp += player.inventory[i].armorHp;
        }
    }
}

void showInventory(Player& player) {
    int inventoryInput = 0;
    int throwAwayInput = 0;
    std::vector<int> consumableIndices;

    std::cout << "획득한 유물 아이템:" << std::endl;
    for (int i = 0; i < player.inventory.size(); i++) {
        if (player.inventory[i].itemType == RELICS)
        {
            std::cout << "\n" << player.inventory[i].name;
            if (player.inventory[i].weaponAtk > 0) {
                std::cout << " | 추가 공격력: " << player.inventory[i].weaponAtk;
            }
            if (player.inventory[i].armorDef > 0) {
                std::cout << " | 추가 방어력: " << player.inventory[i].armorDef;
            }
            if (player.inventory[i].armorHp > 0) {
                std::cout << " | 추가 체력: " << player.inventory[i].armorHp;
            }
        }
    }

    std::cout << "\n------------------------------" << std::endl;
    std::cout << "\n소비 아이템:" << std::endl;
    for (int i = 0; i < player.inventory.size(); i++) {
        if (player.inventory[i].itemType == CONSUMABLE)
        {
            consumableIndices.push_back(i);
            std::cout << i + 1 << ". " << player.inventory[i].name << " | 회복량: " << player.inventory[i].hp << std::endl;
        }
    }

    if (consumableIndices.empty()) {
        std::cout << "(사용 가능한 아이템이 없습니다.)" << std::endl;
    }

    std::cout << "\n0. 돌아가기" << std::endl;
    std::cout << "\n번호를 입력해주세요: ";
    std::cin >> inventoryInput;

    if (inventoryInput == 0) {
        return;
    }

    if (inventoryInput > consumableIndices.size()) {
        std::cout << "\n잘못된 입력입니다." << std::endl;
        system("pause");
        return;
    }

    // 아이템 사용 로직 (유연한 대응)
    int targetIdx = consumableIndices[inventoryInput - 1]; // 실제 인벤토리 배열상의 위치
    Item& selectedItem = player.inventory[targetIdx];

    std::cout << "\n[" << inventoryInput << "번 아이템 " << selectedItem.name << "]을(를) 사용했습니다!" << std::endl;

    // 체력 회복 (최대 체력 제한)
    int healAmount = selectedItem.hp;
    player.stat.hp = std::min(player.stat.hp + healAmount, player.stat.maxHp + player.armorHp);

    // 사용한 아이템 삭제
    player.inventory.erase(player.inventory.begin() + targetIdx);

    system("pause");

    if (inventoryInput > player.inventory.size()) {
        std::cout << "\n잘못된 입력입니다." << std::endl;
        return;
    }
	// 아이템 버리기 로직 (구현 할지 말지 고민중 why. 판매 기능이 있기에 버리기를 추가하는것보다 그냥 판매 기능을 활용하는 것이 더 나아보임)
}

void showEnding(Player& player) {
    system("cls");
    std::cout << "========================================" << std::endl;
    std::cout << "        ★ 축하합니다! 보스를 물리쳤습니다! ★" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\n당신은 마침내 던전의 최상층에 도달하여" << std::endl;
    std::cout << "세상을 위협하던 보스를 제압했습니다." << std::endl;

    std::cout << "\n[ 최종 기록 ]" << std::endl;
    std::cout << "- 이름: " << player.stat.name << std::endl;
    std::cout << "- 최종 레벨: " << player.level << std::endl;
    std::cout << "- 수집한 골드: " << player.gold << " Gold" << std::endl;

    std::cout << "\n[ 획득한 전설적인 유물들 ]" << std::endl;
    for (const auto& item : player.inventory) {
        if (item.itemType == RELICS) {
            std::cout << "- " << item.name << std::endl;
        }
    }

    std::cout << "\n플레이해주셔서 감사합니다!" << std::endl;
    std::cout << "아무 키나 누르면 메인 화면으로 돌아갑니다." << std::endl;

    // 캐릭터 소멸 또는 초기화 (엔딩을 봤으니)
    player.stat.name = "Unknown";

    system("pause");
    return;
}

void gameLoop(Player& player, int& characterCount)
{
    std::vector<Item> shopStock;
    ramdomItemList(player, shopStock);
    int playingInput = 0;
	std::string restInput;
    while (true) {
        refreshStatus(player);
        system("cls");
        std::cout << "이름: " << player.stat.name << "   |   " << "소지골드: " << player.gold << "    |   " << "현재 층: " << player.floor << std::endl;
        std::cout << "\n레벨: " << player.level << "   |   " << "경험치" << player.currentExp << std::endl;
        std::cout << "\n체력: " << player.stat.hp << "/" << player.stat.maxHp + player.armorHp << std::endl;
        std::cout << "\n공격력: " << player.stat.atk + player.weaponAtk << "   |   " << "방어력: " << player.stat.def + player.armorDef << std::endl;

        std::cout << "\n행동을 선택하세요." << std::endl;
        std::cout << "\n1. 대화하기   2. 탐험하기     3. 층 올라가기     4.휴식하기     5. 가방 열기    6. 저장후 종료하기" << std::endl;
        std::cout << "\n입력: ";
        std::cin >> playingInput;
        if (playingInput == 1)
        {
            showShop(player, shopStock);
        }
        else if (playingInput == 2)
        {
            system("cls");
            std::cout << "\n탐험하기를 선택하셨습니다." << std::endl;
            std::cout << "\n적을 찾아 탐험을 시작합니다..." << std::endl;
			if (player.floor == 10) {
                Monster bossMonster = CreateMonster(4);
                std::cout << "\n보스 몬스터 [" << bossMonster.stat.name << "](이)가 나타났다!" << std::endl;
                bool isVictory = startBattle(player, bossMonster);
                if (isVictory && bossMonster.variant == 2) { // 2를 보스라고 가정
                    if (player.floor == 10) {
                        showEnding(player); // 엔딩 함수 호출
                        return; // 게임 루프 종료 및 메인 메뉴로
                    }
                }
                if (!isVictory)
                {
                    player.stat.name = "Unknown";
                    std::cout << "\n캐릭터가 소멸되었습니다. 메인 메뉴로 돌아갑니다." << std::endl;
                    system("pause");
                    return;
                }
            }
            else {
                int randomType = (rand() % 3) + 1;
                Monster currentMonster = CreateMonster(randomType);

                std::cout << "\n앗! [" << currentMonster.stat.name << "](이)가 나타났다!" << std::endl;

                std::cout << "\n1. 싸우기   2. 도망가기" << std::endl;
                std::cout << "\n입력: ";
                std::cin >> playingInput;
                if (playingInput == 1) {

                    bool isVictory = startBattle(player, currentMonster);

                    if (!isVictory)
                    {
                        player.stat.name = "Unknown";

                        std::cout << "\n캐릭터가 소멸되었습니다. 메인 메뉴로 돌아갑니다." << std::endl;
                        system("pause");
                        return;
                    }
                }
                else if (playingInput == 2) {
                    std::cout << "\n도망가기를 선택하셨습니다." << std::endl;
                }
            }
        }
        else if (playingInput == 3)
        {
            system("cls");
            std::cout << "\n층 올라가기를 선택하셨습니다." << std::endl;
            floorTransition(player);
            shopStock.clear();
            ramdomItemList(player, shopStock);
        }
        else if (playingInput == 4)
        {
            system("cls");
            std::cout << "\n휴식하기를 선택하셨습니다." << std::endl;
			std::cout << "\n휴식을 취하면 체력이 완전히 회복되지만, 골드가 100 소모됩니다." << std::endl;
			std::cout << "\n휴식을 취하시겠습니까? (네/아니오): ";
            std::cin >> restInput;
            if (restInput == "네") {
                if (player.gold >= 100) {
                    rest(player);
                }
            } else if (restInput == "아니오") {
                std::cout << "\n휴식을 취하지 않기로 선택하셨습니다." << std::endl;
            } else {
                std::cout << "\n잘못된 입력입니다. 휴식을 취하지 않기로 선택하셨습니다." << std::endl;
			}
        }
        else if (playingInput == 5)
        {
            system("cls");
            std::cout << "\n가방 열기를 선택하셨습니다." << std::endl;
			showInventory(player);
        }
        else if (playingInput == 6)
        {
            system("cls");
            std::cout << "\n저장후 종료하기를 선택하셨습니다." << std::endl;
            return;
        }
        else
        {
            std::cout << "\n잘못된 입력입니다." << std::endl;
        }
    }
}

void rest(Player& player) {
    std::cout << "\n휴식을 취합니다..." << std::endl;
    player.gold -= 100; //휴식 비용
    player.stat.hp = player.stat.maxHp + player.armorHp;
    std::cout << "\n체력이 완전히 회복되었습니다!" << std::endl;
    system("pause");
}

void showShop(Player& player, std::vector<Item>& shopStock)
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

        std::cout << "\n대화하기를 선택하셨습니다." << std::endl;
        std::cout << "\n상인" << std::endl;
        showMerchantTalk();
        std::cout << "\n1. 구매하기   2. 판매하기     3. 돌아가기" << std::endl;
        std::cout << "\n입력: ";
        std::cin >> shopInput;
        if (shopInput == 1)
        {
            std::cout << "\n구매하기를 선택하셨습니다." << std::endl;
		    system("cls");
            if (conCount >= 3)
            {
                std::cout << "\n소비 아이템 가득참!!" << std::endl;
            }
            std::cout << "\n구매 물품 목록" << std::endl;
            std::cout << "\n 0. 돌아가기" << std::endl;
            showShopItem(player, shopStock);
		    std::cout << "\n------------------------------" << std::endl;
		    std::cout << "\n현재 골드: " << player.gold << std::endl;
            std::cout << "\n번호를 입력하세요: ";
            std::cin >> buyInput;
            // 구매 로직
            if (buyInput == 0) {
			    std::cout << "\n돌아가기를 선택하셨습니다." << std::endl;
                break;
		    }

            if (buyInput < 1 || buyInput > shopStock.size()) {
                std::cout << "\n잘못된 입력입니다." << std::endl;
            }
            else {
                if (shopStock[buyInput - 1].itemType == CONSUMABLE && conCount >= 3)
                {
                    std::cout << "\n소비 아이템은 최대 3개까지만 소지할 수 있습니다." << std::endl;
                    system("pause");
                    return;
				}

                Item selectedItem = shopStock[buyInput - 1];
                if (player.gold >= selectedItem.price) {
                    player.gold -= selectedItem.price;
                    player.inventory.push_back(selectedItem);
					shopStock.erase(shopStock.begin() + (buyInput - 1));
                    std::cout << "\n" << selectedItem.name << "을(를) 구매했습니다! 남은 골드: " << player.gold << std::endl;
				    system("pause");
                }
                else {
                    std::cout << "\n골드가 부족합니다." << std::endl;
                    system("pause");

                }
            }
        }
        else if (shopInput == 2)
        {
            std::cout << "\n판매하기를 선택하셨습니다." << std::endl;
            system("cls");
            std::cout << "\n판매 물품 목록" << std::endl;
			std::cout << "\n 현재 골드: " << player.gold << std::endl;
			std::cout << "\n 0. 돌아가기" << std::endl;
            showPlayerItem(player);
            std::cout << "\n판매할 물품 번호를 입력하세요: ";
            std::cin >> sellInput;
            // 판매 로직
            if (sellInput == 0) {
                std::cout << "\n돌아가기를 선택하셨습니다." << std::endl;
                break;
            }

            if (sellInput < 1 || sellInput > player.inventory.size()) {
                std::cout << "\n잘못된 입력입니다." << std::endl;
            }
            else {
                Item selectedItem = player.inventory[sellInput - 1];
                player.gold += selectedItem.price * 0.5;
                player.inventory.erase(player.inventory.begin() + (sellInput - 1));
                std::cout << "\n" << selectedItem.name << "을(를) 판매했습니다! 현재 골드: " << player.gold << std::endl;
                system("pause");
            }
        }
        else if (shopInput == 3)
        {
            std::cout << "\n돌아가기를 선택하셨습니다." << std::endl;
            break;
        }
        else
        {
            std::cout << "\n잘못된 입력입니다." << std::endl;
        }
    }
}

void ramdomItemList(Player& player, std::vector<Item>& shopStock) {
    // 각 층마다 한번씩만 물품을 파는 것으로 가정하고, 층마다 파는 물품이 다르다고 가정
    // 예시로 저층에선 체력 회복 물약, 중층부터 확률에 따라 유물 아이템이 등장하는 것
    // 층마다 파는 물품이 같을수도 다를수도
    // 가아끔 아주 희귀한 유물 아이템이 등장할 수도 있음

      int floor = player.floor;
      shopStock.push_back(ItemList(1));
    std::cout << "\n" << "1. " << shopStock[0].name << " | 가격: " << shopStock[0].price;
    for (int i = 1; i <= 4; i++) 
    {
        int randomCnt = rand() % 100;
        int pickedItem = (floor * 3) + randomCnt;

        if (pickedItem < 90) {
            int randomType = (rand() % 3 + 1);
            Item itemList = ItemList(randomType);
            shopStock.push_back(itemList);
            std::cout << "\n" << (i + 1) << ". " << shopStock[i].name << " | 가격: " << shopStock[i].price;
        } else {
            int randomType = (rand() % 7 + 1);
            Item itemList = ItemList(randomType);
            shopStock.push_back(itemList);
            std::cout << "\n" << (i + 1) << ". " << shopStock[i].name << " | 가격: " << shopStock[i].price;
        }
    }
}

void showShopItem(Player& player, std::vector<Item>& shopStock) {
    // 물품 출력
    for (int i = 0; i <= shopStock.size() - 1; i++) {
        printf("\n %d. %s | 가격: %d\n", i+1 ,shopStock[i].name.c_str(), shopStock[i].price);
    }
}

void showPlayerItem(Player& player) {
    for (size_t i = 0; i < player.inventory.size(); i++) {
        std::cout << "\n" << (i + 1) << ". " << player.inventory[i].name;
    }
}

void showMerchantTalk()
{
    std::vector<std::string> talks = {
        "오늘은 좋은 날이군! 혹시 필요한 물건이 있나?",
        "이번 층에서는 이상한 소문이 들려오던데, 조심하는 게 좋을 거야.",
        "최근에 이 층엔 강력한 몬스터가 나타났다는 소문이 있어. 조심해야 해!",
        "이번 층에는 숨겨진 보물이 있다고 하는데, 한번 찾아보는 건 어때?",
        "요즘은 모험가들이 많이 늘어서, 좋은 장비를 구하기가 어려워졌어.",
        "물건을 사러 왔나? 혹 그대가 좋은 물건이 있다면 내 구매 할 의향도 있네!",
        "가끔은 일어나서 기지게를 피는게 좋네."
    };
    int randomIndex = rand() % talks.size();
    std::cout << talks[randomIndex] << std::endl;
}

bool startBattle(Player& player, Monster& monster)
{
    while (player.stat.hp > 0 && monster.stat.hp > 0)
    {
        system("pause");
        if (player.stat.speed >= monster.stat.speed) 
        {
            int damageToMonster = std::max(0, (player.stat.atk + player.weaponAtk) - monster.stat.def);
            monster.stat.hp -= damageToMonster;
            std::cout << "플레이어가 " << damageToMonster << "의 피해를 입혔습니다! 몬스터 HP: " << monster.stat.hp << "/" << monster.stat.maxHp << std::endl;
            if (monster.stat.hp <= 0) 
            {
                std::cout << "몬스터를 처치했습니다!" << std::endl;
                player.AddExperience(monster.giveExp);
                player.gold += monster.giveGold;
                std::cout << "골드 " << monster.giveGold << "을 획득했습니다! 현재 골드: " << player.gold << std::endl;
                if (monster.variant == 1) {
                    player.floorCount++;
                    std::cout << "다음 층으로 이동 할 수 있습니다!" << std::endl;
                }
                system("pause");
                return true;
            }
            int damageToPlayer = std::max(0, monster.stat.atk - (player.stat.def + player.armorDef));
            player.stat.hp -= damageToPlayer;
            std::cout << "몬스터가 " << damageToPlayer << "의 피해를 입혔습니다! 플레이어 HP: " << player.stat.hp << "/" << player.stat.maxHp << std::endl;
            if (player.stat.hp <= 0) 
            {
                std::cout << "플레이어가 패배했습니다..." << std::endl;
                system("pause");
                return false;
            }
        }   
        else 
        {
            int damageToPlayer = std::max(0, monster.stat.atk - player.stat.def);
            player.stat.hp -= damageToPlayer;
            std::cout << "몬스터가 " << damageToPlayer << "의 피해를 입혔습니다! 플레이어 HP: " << player.stat.hp << "/" << player.stat.maxHp << std::endl;
            if (player.stat.hp <= 0)
            {
                std::cout << "플레이어가 패배했습니다..." << std::endl;
                system("pause");
                return false;
            }
            int damageToMonster = std::max(0, player.stat.atk - monster.stat.def);
            monster.stat.hp -= damageToMonster;
            std::cout << "플레이어가 " << damageToMonster << "의 피해를 입혔습니다! 몬스터 HP: " << monster.stat.hp << "/" << monster.stat.maxHp << std::endl;
            if (monster.stat.hp <= 0)
            {
                std::cout << "몬스터를 처치했습니다!" << std::endl;
                player.AddExperience(monster.giveExp);
				player.inventory.push_back(ItemList(5));
                player.gold += monster.giveGold;
                std::cout << "골드 " << monster.giveGold << "을 획득했습니다! 현재 골드: " << player.gold << std::endl;
                if (monster.variant == 1) {
                    player.floorCount++;
                    std::cout << "다음 층으로 이동 할 수 있습니다!" << std::endl;
                }
                system("pause");
                return true;
            }
        }
    }
    return false;
}

void floorTransition(Player& player) {
    if (player.floorCount >= 1) {
        player.floor++;
        player.floorCount = 0;
        std::cout << "다음 층으로 이동합니다." << std::endl;
        system("pause");
    }
    else {
        std::cout << "아직 다음 층으로 이동할 수 없습니다." << std::endl;
        system("pause");
    }
}

int main()
{
    srand((unsigned int)time(0));

	std::vector<Player> saveSlots; // 최대 3개의 캐릭터 저장 슬롯
    int characterCount = 0;
    while (true)
    {
        startMenu(saveSlots, characterCount);
        // startMenu가 종료(return)되면 다시 이 while문의 처음으로 돌아와 메뉴를 보여줍니다.
    }

    return 0;
}
