#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
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
	int maxExp = 100;
    int level = 0;


    void AddExperience(int exp) {
        currentExp += exp;
        std::cout << exp << "의 경험치를 획득했습니다!\n";

        while (currentExp >= maxExp) {
            LevelUp();
        }
    }

    void LevelUp() {
        currentExp -= maxExp;
        level++;

        maxExp = static_cast<int>(maxExp * 1.2);

        std::cout << "★ 레벨 업! 현재 레벨: " << level << " ★\n";
    }
};

struct Monster {
    Unit stat;        
    int giveExp = 0;
    int giveGold = 0;
};

void characterMenu(Player* saveSlots, int& characterCount);
void createCharacter(Player* saveSlots, int& characterCount);
void gameLoop(Player& player);
void ShowShop();
void ShowMerchantTalk();

static void startMenu(Player* saveSlots, int& characterCount)
{
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
            std::cout << "0. 종료하기" << std::endl;
            std::cout << "선택: ";

            int select = 0;
            std::cin >> select;

            if (select == 0) return;

            if (select > 0 && select <= characterCount) {
                system("cls");
                int targetIndex = select - 1;

                std::cout << "[" << saveSlots[targetIndex].stat.name << "] 캐릭터를 선택했습니다!" << std::endl;

				gameLoop(saveSlots[targetIndex]);

                break;
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
        newMonster.stat = { "슬라임", 30, 30, 5, 2, 5, 10 }; // 이름, HP, MaxHP, ATK, DEF, SPD, EVA
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

void gameLoop(Player& player) 
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
            ShowShop();
        }
        else if (playingInput == 2)
        {
            system("cls");
            std::cout << "\n탐험하기를 선택하셨습니다." << std::endl;
            std::cout << "\n적을 찾아 탐험을 시작합니다..." << std::endl;

            // 1~3번 중 랜덤하게 몬스터 한 마리를 생성
            int randomType = (rand() % 3) + 1;
            Monster currentMonster = CreateMonster(randomType);

            std::cout << "\n앗! [" << currentMonster.stat.name << "](이)가 나타났다!" << std::endl;
            system("pause");

            // 여기서 나중에 Battle(player, currentMonster); 함수 부르기
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

void ShowShop() 
{
    system("cls");
    int shopInput = 0;
    int buyInput = 0;
    int sellInput = 0;

    std::cout << "\n대화하기를 선택하셨습니다." << std::endl;
    std::cout << "\n상인" << std::endl;
    ShowMerchantTalk();
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

void ShowMerchantTalk() 
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


int main()
{
    srand((unsigned int)time(0));

    Player saveSlots[3] = {};
    int characterCount = 0;

    startMenu(saveSlots, characterCount);
    
	return 0;
}
