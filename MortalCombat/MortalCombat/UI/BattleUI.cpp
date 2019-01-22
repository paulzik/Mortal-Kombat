#include "BattleUI.h"
#include "UIManager.h"
#include <string>

using namespace std;

BattleUI::BattleUI(Fighter* _player1, Fighter* _player2)
{
	renderer = UIManager::Get()->GetRenderer();
	player1 = _player1;
	player2 = _player2;
	tag = SceneTag::Battle;
	InitializeUI();

}


void BattleUI::InitializeUI() 
{
	player1UI.lifebarRed = InitializeImageElement("./Bitmaps/BattleElements/lifebar.png", {42,58,163 * 2,24 });
	player1UI.lifebarGreen = InitializeImageElement("./Bitmaps/BattleElements/lifebarGreen.png", { 44,60,322,20 });
	player1UI.name = InitializeImageElement("./Bitmaps/BattleElements/ScorpionName.png", { 59,57,224,25 });

	player1UI.coins.push_back(InitializeImageElement("./Bitmaps/BattleElements/coin.png", { 50,90,20,20 }));
	//player1UI.coins.push_back(InitializeImageElement("./Bitmaps/BattleElements/coin.png", { 75,90,20,20 }));

	player2UI.lifebarRed = InitializeImageElement("./Bitmaps/BattleElements/lifebar.png", { 412,58,163 * 2,24 });
	player2UI.lifebarGreen = InitializeImageElement("./Bitmaps/BattleElements/lifebarGreen.png", { 414,60,322,20 });
	player2UI.name = InitializeImageElement("./Bitmaps/BattleElements/SubzeroName.png", { 570,57,224,25 });

}

void BattleUI::RenderUI()
{

	player1UI.lifebarGreen->imageRect = { 44,60, (322 * player1->GetHealth())/100,20 };
	player2UI.lifebarGreen->imageRect = { 414 + 322 - (322 * player2->GetHealth())/100,60, (322 * player2->GetHealth()) / 100,20 };

	UICanvas::RenderUI();
}


