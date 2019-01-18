#include "BattleUI.h"
#include <string>

using namespace std;

BattleUI::BattleUI(SDL_Renderer* _renderer, Fighter* _player1, Fighter* _player2)
{
	renderer = _renderer;
	player1 = _player1;
	player2 = _player2;

	InitializeUI();

}


void BattleUI::InitializeUI() 
{
	InitializeImageElement("./Bitmaps/BattleElements/lifebar.png", { 42,58,163 * 2,12 * 2 });
	InitializeImageElement("./Bitmaps/BattleElements/lifebar.png",  { 412,58,163 * 2,12 * 2 });

	player1Lifebar = InitializeImageElement("./Bitmaps/BattleElements/lifebarGreen.png",  { 44,60,322,20 });
	player2Lifebar = InitializeImageElement("./Bitmaps/BattleElements/lifebarGreen.png", { 414,60,322,20 });

	player1Coins = InitializeImageElement("./Bitmaps/BattleElements/coin.png",  { 50,90,10 * 2,10 * 2 });
	player2Coins = InitializeImageElement("./Bitmaps/BattleElements/coin.png",  { 80,90,10 * 2,10 * 2 });
}

void BattleUI::RenderUI()
{
	player1Lifebar->imageRect = { 44,60, (322 * player1->GetHealth())/100,10 * 2 };
	player2Lifebar->imageRect = { 414 + 322 - (322 * player1->GetHealth())/100,60, (322 * player1->GetHealth()) / 100,10 * 2 };

	UICanvas::RenderUI();
}


