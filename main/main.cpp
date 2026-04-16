// encoding: UTF-8
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "Core.h"
#include "Player.h"
#include "GameSystem.h"

int main()
{
    srand((unsigned int)time(0));

    GameSystem game;

	std::vector<Player> saveSlots; // 최대 3개의 캐릭터 저장 슬롯
    int characterCount = 0;
    while (true)
    {
        game.startMenu(saveSlots, characterCount);
        // startMenu가 종료(return)되면 다시 이 while문의 처음으로 돌아와 메뉴를 보여줍니다.
    }

    return 0;
}
