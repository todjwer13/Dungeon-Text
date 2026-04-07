#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>

struct Unit {
    std::string name = "Unknown";
    int hp = 0;
    int maxHp = 0;
    int atk = 0;
    int def = 0;
    int speed = 0;
    int evasion = 0;
};

struct Player {
    Unit stat;
    int mp = 0;
    int maxMp = 0;
    int gold = 0;
    int currentExp = 0;
    int maxExp = 50;
    int level = 0;
    

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
        std::cout << "★ 최대 체력이 올랐습니다 최대체력: " << stat.maxHp << " ★\n";
		maxMp += 10;
        std::cout << "★ 최대 마나이 올랐습니다 최대마나: " << maxMp << " ★\n";
		stat.hp = stat.maxHp;
        std::cout << "★ 체력이 회복되었습니다. ★\n";
		mp = maxMp;
        std::cout << "★ 마나가 회복되었습니다. ★\n";
		stat.atk += 5;
        std::cout << "★ 공격력이 5만큼 증가하였습니다. ★\n";
		stat.def += 2;
        std::cout << "★ 방어력이 2만큼 증가하였습니다. ★\n";
    }
};

struct Monster {
    Unit stat;
    int giveExp = 0;
    int giveGold = 0;
};

void characterMenu(Player* saveSlots, int& characterCount);
void createCharacter(Player* saveSlots, int& characterCount);
void gameLoop(Player& player, int& characterCount);
bool startBattle(Player& player, Monster& monster);
Monster CreateMonster(int type);
void showShop(Player& player);
void showMerchantTalk();
void deleteCharacter(Player* saveSlots, int& characterCount);
void extinctionCharacter(Player& player, int& characterCount);

static void startMenu(Player* saveSlots, int& characterCount)
{
    if (characterCount > 0) {
        for (int i = 0; i < 3; i++) {
            if (saveSlots[i].stat.name == "Unknown")
            {
                for (int j = i; j < characterCount - 1; j++) {
                    saveSlots[j] = saveSlots[j + 1];
                }
                characterCount--;
            }
        }
        
	}
    

    system("cls");
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
    }
}

void characterMenu(Player* saveSlots, int& characterCount)
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

// 층수나 난이도에 따라 몬스터를 생성해주는 함수
Monster CreateMonster(int type) {
    Monster newMonster;

    switch (type) {
    case 1:
        newMonster.stat = { "슬라임", 30, 30, 6, 2, 5, 10 }; // 이름, HP, MaxHP, ATK, DEF, SPD, EVA
        newMonster.giveExp = 10;
        newMonster.giveGold = 20;
        break;
    case 2:
        newMonster.stat = { "고블린", 50, 50, 12, 5, 8, 5 };
        newMonster.giveExp = 25;
        newMonster.giveGold = 50;
        break;
    case 3:
        newMonster.stat = { "오크", 100, 100, 20, 15, 4, 0 };
        newMonster.giveExp = 60;
        newMonster.giveGold = 150;
        break;
    }
    return newMonster;
}

void createCharacter(Player* saveSlots, int& characterCount) {
    if (characterCount >= 3) {
        system("cls");
        std::cout << "캐릭 슬롯이 가득 찼습니다!" << std::endl;
        return;
    }

    std::cout << "이름: ";
    std::string newName;
    std::cin >> newName;

    saveSlots[characterCount].stat.name = newName;
    saveSlots[characterCount].stat.hp = 100;
    saveSlots[characterCount].stat.maxHp = 100;
    saveSlots[characterCount].stat.atk = 15;
    saveSlots[characterCount].stat.def = 5;
    saveSlots[characterCount].stat.speed = 10;
    saveSlots[characterCount].stat.evasion = 5;
    saveSlots[characterCount].mp = 100;
    saveSlots[characterCount].maxMp = 100;
    saveSlots[characterCount].gold = 500;
    saveSlots[characterCount].currentExp = 0;
    saveSlots[characterCount].level = 1;

    characterCount++;
    system("cls");
    std::cout << "캐릭터 [" << newName << "] (이)가 생성되었습니다!" << std::endl;
    system("pause");
    return;
}

void deleteCharacter(Player* saveSlots, int& characterCount) {
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
    for (int i = deleteInput - 1; i < characterCount - 1; i++) {
        saveSlots[i] = saveSlots[i + 1];
    }
    characterCount--;
    system("cls");
    std::cout << "캐릭터가 삭제되었습니다!" << std::endl;
    system("pause");
}

void gameLoop(Player& player, int& characterCount)
{
    int playingInput = 0;
    while (true) {
        system("cls");
        std::cout << "이름: " << player.stat.name << "   |   " << "소지골드: " << player.gold << std::endl;
        std::cout << "\n레벨: " << player.level << "   |   " << "경험치" << player.currentExp << std::endl;
        std::cout << "\n체력: " << player.stat.hp << "/" << player.stat.maxHp << "   |   " << "마나: " << player.mp << "/" << player.maxMp << std::endl;
        std::cout << "\n공격력: " << player.stat.atk << "   |   " << "방어력: " << player.stat.def << std::endl;

        std::cout << "\n행동을 선택하세요." << std::endl;
        std::cout << "\n1. 대화하기   2. 탐험하기     3. 층 이동하기     4.휴식하기     5. 장비 강화    6. 저장후 종료하기" << std::endl;
        std::cout << "\n입력: ";
        std::cin >> playingInput;
        if (playingInput == 1)
        {
            showShop(player);
        }
        else if (playingInput == 2)
        {
            system("cls");
            std::cout << "\n탐험하기를 선택하셨습니다." << std::endl;
            std::cout << "\n적을 찾아 탐험을 시작합니다..." << std::endl;

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
        else if (playingInput == 3)
        {
            system("cls");
            std::cout << "\n층 이동하기를 선택하셨습니다." << std::endl;
        }
        else if (playingInput == 4)
        {
            system("cls");
            std::cout << "\n휴식하기를 선택하셨습니다." << std::endl;
        }
        else if (playingInput == 5)
        {
            system("cls");
            std::cout << "\n인벤토리 열기를 선택하셨습니다." << std::endl;
        }
        else if (playingInput == 6)
        {
            system("cls");
            std::cout << "\n저장후 종료하기를 선택하셨습니다." << std::endl;
            break;
        }
        else
        {
            std::cout << "\n잘못된 입력입니다." << std::endl;
        }
    }
}

void showShop(Player& player)
{
    system("cls");
    int shopInput = 0;
    int buyInput = 0;
    int sellInput = 0;

    std::cout << "\n대화하기를 선택하셨습니다." << std::endl;
    std::cout << "\n상인" << std::endl;
    showMerchantTalk();
    std::cout << "\n1. 구매하기   2. 판매하기     3. 돌아가기" << std::endl;
    std::cout << "\n입력: ";
    std::cin >> shopInput;
    if (shopInput == 1)
    {
        std::cout << "\n구매하기를 선택하셨습니다." << std::endl;
        std::cout << "\n구매 물품 목록" << std::endl;
        std::cout << "\n1. 체력 회복 물약  2. 마나 회복 물약  3. 공격력 증가 물약" << std::endl;
        std::cout << "\n구매할 물품 번호를 입력하세요: ";
        std::cin >> buyInput;
    }
    else if (shopInput == 2)
    {
        std::cout << "\n판매하기를 선택하셨습니다." << std::endl;
        std::cout << "\n판매 물품 목록" << std::endl;
        std::cout << "\n1. 체력 회복 물약  2. 마나 회복 물약  3. 공격력 증가 물약" << std::endl;
        std::cout << "\n판매할 물품 번호를 입력하세요: ";
        std::cin >> sellInput;
    }
    else if (shopInput == 3)
    {
        std::cout << "\n돌아가기를 선택하셨습니다." << std::endl;
    }
    else
    {
        std::cout << "\n잘못된 입력입니다." << std::endl;
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
            int damageToMonster = std::max(0, player.stat.atk - monster.stat.def);
            monster.stat.hp -= damageToMonster;
            std::cout << "플레이어가 " << damageToMonster << "의 피해를 입혔습니다! 몬스터 HP: " << monster.stat.hp << "/" << monster.stat.maxHp << std::endl;
            if (monster.stat.hp <= 0) 
            {
                std::cout << "몬스터를 처치했습니다!" << std::endl;
                player.AddExperience(monster.giveExp);
                player.gold += monster.giveGold;
                std::cout << "골드 " << monster.giveGold << "을 획득했습니다! 현재 골드: " << player.gold << std::endl;
                system("pause");
                return true;
            }
            int damageToPlayer = std::max(0, monster.stat.atk - player.stat.def);
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
                return false;
            }
            int damageToMonster = std::max(0, player.stat.atk - monster.stat.def);
            monster.stat.hp -= damageToMonster;
            std::cout << "플레이어가 " << damageToMonster << "의 피해를 입혔습니다! 몬스터 HP: " << monster.stat.hp << "/" << monster.stat.maxHp << std::endl;
            if (monster.stat.hp <= 0)
            {
                std::cout << "몬스터를 처치했습니다!" << std::endl;
                player.AddExperience(monster.giveExp);
                player.gold += monster.giveGold;
                std::cout << "골드 " << monster.giveGold << "을 획득했습니다! 현재 골드: " << player.gold << std::endl;
                return true;
            }
        }
    }
}


int main()
{
    srand((unsigned int)time(0));

    Player saveSlots[3] = {};
    int characterCount = 0;

    while (true)
    {
        startMenu(saveSlots, characterCount);
        // startMenu가 종료(return)되면 다시 이 while문의 처음으로 돌아와 메뉴를 보여줍니다.
    }

    return 0;
}
