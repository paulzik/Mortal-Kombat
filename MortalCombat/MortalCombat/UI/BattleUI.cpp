#include "BattleUI.h"
#include <string>
using namespace std;

BattleUI::BattleUI(SDL_Renderer* _renderer)
{
	renderer = _renderer;
	InitializeUI();

}


void BattleUI::InitializeUI() 
{
	InitializeImageElement("./Bitmaps/BattleElements/lifebar.png", { 42,58,163 * 2,12 * 2 });
	InitializeImageElement("./Bitmaps/BattleElements/lifebar.png",  { 412,58,163 * 2,12 * 2 });

	player1Lifebar = InitializeImageElement("./Bitmaps/BattleElements/lifebarGreen.png",  { 44,60,120 * 2,10 * 2 });
	player2Lifebar = InitializeImageElement("./Bitmaps/BattleElements/lifebarGreen.png", { 414,60,120 * 2,10 * 2 });

	player1Coins = InitializeImageElement("./Bitmaps/BattleElements/coin.png",  { 50,90,10 * 2,10 * 2 });
	player2Coins = InitializeImageElement("./Bitmaps/BattleElements/coin.png",  { 80,90,10 * 2,10 * 2 });
}


