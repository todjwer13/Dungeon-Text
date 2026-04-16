#pragma once
#include "Player.h"

class GameSystem
{
public:
	void startMenu(std::vector<Player>& saveSlots, int& characterCount);

	void gameLoop(Player& player, int& characterCount);

	void showShop(Player& player, std::vector<Item>& shopStock);

	void showShopItem(Player& player, std::vector<Item>& shopStock);

	void showMerchantTalk();

	bool startBattle(Player& player, Monster& monster);

	void floorTransition(Player& player);

	void randomItemList(Player& player, std::vector<Item>& shopStock);

	Item ItemList(int type);

	// 몬스터를 생성해주는 함수
	Monster CreateMonster(int type);

	void characterMenu(std::vector<Player>& saveSlots, int& characterCount);

	void cleanUpCharacters(std::vector<Player>& saveSlots, int& characterCount);


	void createCharacter(std::vector<Player>& saveSlots, int& characterCount);

	void deleteCharacter(std::vector<Player>& saveSlots, int& characterCount);
};