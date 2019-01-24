#include "BattleUI.h"
#include "UIManager.h"
#include <string>
#include <SDL_ttf.h>
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

	//Initialize Timer
	for (size_t i = 0; i < 10; i++)
	{
		string file = "./Bitmaps/BattleElements/Timer/" + std::to_string(i) + ".png";
		timerTextures.push_back(IMG_LoadTexture(renderer, file.c_str()));
		string file2 = "./Bitmaps/BattleElements/Timer/" + std::to_string(i) + ".png";
		pointsTextures.push_back(IMG_LoadTexture(renderer, file.c_str()));
	}
	timer = SDL_GetTicks();

	//Initialize Points

}

void BattleUI::RenderUI()
{
	//Render Bars
	player1UI.lifebarGreen->imageRect = { 44,60, (322 * player1->GetHealth())/100,20 };
	player2UI.lifebarGreen->imageRect = { 414 + 322 - (322 * player2->GetHealth())/100,60, (322 * player2->GetHealth()) / 100,20 };

	//Render Timer
	if (SDL_GetTicks() - timer> 1000) {
		timer = SDL_GetTicks();
		if(countdown > 1)
			countdown--;
	}
	SDL_Rect rect = SDL_Rect({ 360 ,14, 32, 38 });
	SDL_RenderCopy(renderer, timerTextures[countdown/10], NULL, &rect);

	SDL_Rect rect2 = SDL_Rect({ 392 ,14, 32, 38 });
	SDL_RenderCopy(renderer, timerTextures[countdown%10], NULL, &rect2);

	//Render Points
	//TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

	//SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	//SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	//SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

	//SDL_Rect Message_rect; //create a rect
	//Message_rect.x = 0;  //controls the rect's x coordinate 
	//Message_rect.y = 0; // controls the rect's y coordinte
	//Message_rect.w = 100; // controls the width of the rect
	//Message_rect.h = 100; // controls the height of the rect

	////Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

	////Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	//SDL_RenderCopy(renderer, Message, NULL, &Message_rect);


	UICanvas::RenderUI();
}



