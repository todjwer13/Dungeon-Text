#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Player
{
    std::string name = "Unknown";
    int hp = 0;
    int maxHp = 0;
    int atk = 0;
    int def = 0;
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

void characterMenu(Player* saveSlots, int& characterCount);
void createCharacter(Player* saveSlots, int& characterCount);
void gameLoop(Player& player);
void ShowShop();
void ShowMerchantTalk();

void startMenu(Player* saveSlots, int& characterCount)
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
                std::cout << i + 1 << ". " << saveSlots[i].name << " (Lv." << saveSlots[i].level << ")" << std::endl;
            }
            std::cout << "0. 종료하기" << std::endl;
            std::cout << "선택: ";

            int select = 0;
            std::cin >> select;

            if (select == 0) return;

            if (select > 0 && select <= characterCount) {
                system("cls");
                int targetIndex = select - 1;

                std::cout << "[" << saveSlots[targetIndex].name << "] 캐릭터를 선택했습니다!" << std::endl;

				gameLoop(saveSlots[targetIndex]);

                break;
            }
            else {
                std::cout << "\n잘못된 번호입니다. 다시 선택해주세요." << std::endl;
            }
        }
    }
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

    saveSlots[characterCount].name = newName;
    saveSlots[characterCount].hp = 100;
    saveSlots[characterCount].maxHp = 100;
    saveSlots[characterCount].mp = 100;
    saveSlots[characterCount].maxMp = 100;
    saveSlots[characterCount].atk = 10;
    saveSlots[characterCount].def = 10;
    saveSlots[characterCount].gold = 1000;
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
		std::cout << "이름: " << player.name << "   |   " << "소지골드: " << player.gold << std::endl;
        std::cout << "\n레벨: " << player.level << "   |   " << "경험치" << player.currentExp << std::endl;
        std::cout << "\n체력: " << player.hp << "/" << player.maxHp << "   |   " << "마나: " << player.mp << "/" << player.maxMp << std::endl;
        std::cout << "\n공격력: " << player.atk << "   |   " << "방어력: " << player.def << std::endl;

        std::cout << "\n행동을 선택하세요." << std::endl;
        std::cout << "\n1. 대화하기   2. 탐험하기     3. 휴식하기     4. 인벤토리 열기    5. 저장후 종료하기" << std::endl;
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
        }
        else if (playingInput == 3)
        {
            system("cls");
            std::cout << "\n휴식하기를 선택하셨습니다." << std::endl;
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
    srand(time(NULL));
    Player saveSlots[3] = {};
    int characterCount = 0;
    startMenu(saveSlots, characterCount);
    
	return 0;
}
