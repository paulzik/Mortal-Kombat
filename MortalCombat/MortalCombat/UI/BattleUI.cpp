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
	flipped = false;
	bmXs[0] = 320;
	bmXs[1] = 300;
	bmXs[2] = 280;
	bmXs[3] = 280;

	bmYs[0] = 150;
	bmYs[1] = 150;
	bmYs[2] = 150;
	bmYs[3] = 150;
	InitializeUI();

	InitializeBattleUIAnimations(renderer);
}


void BattleUI::InitializeUI() 
{
	player1UI.lifebarRed = InitializeImageElement("./Bitmaps/BattleElements/lifebar.png", {42,58,163 * 2,24 });
	player1UI.lifebarGreen = InitializeImageElement("./Bitmaps/BattleElements/lifebarGreen.png", { 44,60,322,20 });
	player1UI.name = InitializeImageElement("./Bitmaps/BattleElements/ScorpionName.png", { 59,57,224,25 });

	string file = "./Bitmaps/BattleElements/coin.png";
	coin = IMG_LoadTexture(renderer, file.c_str());

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

	//Render Coins
	for (int i = 0; i < player1->GetWins(); i++)
	{
		if (player1->GetWins() > 11)
			break;
		SDL_Rect rect3 = SDL_Rect({ 45 + (i*30),90,20,20 });
		SDL_RenderCopy(renderer, coin, NULL, &rect3);
	}
	
	for (int i = 0; i < player2->GetWins(); i++)
	{
		if (player1->GetWins() > 11)
			break;
		SDL_Rect rect3 = SDL_Rect({ 720 - (i * 30),90,20,20 });
		SDL_RenderCopy(renderer, coin, NULL, &rect3);
	}

	UICanvas::RenderUI();
}

void BattleUI::InitializeBattleUIAnimations(SDL_Renderer *renderer)
{
	int index = 2000;
	afh = new AnimationFilmHolder();
	sprites = new SpritesHolder();
	afh->Load("BattleUI", renderer);


	animators = new Animators();

	animators->insert(std::pair<std::string, Animator*>("fight", new FrameRangeAnimator(index++)));
	animators->insert(std::pair<std::string, Animator*>("finishhim", new FrameRangeAnimator(index++)));
	animators->insert(std::pair<std::string, Animator*>("scorpionwins", new FrameRangeAnimator(index++)));
	animators->insert(std::pair<std::string, Animator*>("subzerowins", new FrameRangeAnimator(index++)));

	index = 2000;
	std::map<std::string, Animation*> animations;
	animations.insert(std::pair<std::string, Animation*>("fight", new FrameRangeAnimation(0, 22, 0, 0, 0.065f, true, index++)));
	animations.insert(std::pair<std::string, Animation*>("finishhim", new FrameRangeAnimation(0, 21, 0, 0, 0.1f, true, index++)));
	animations.insert(std::pair<std::string, Animation*>("scorpionwins", new FrameRangeAnimation(0, 2, 0, 0, 0.1f, true, index++)));
	animations.insert(std::pair<std::string, Animation*>("subzerowins", new FrameRangeAnimation(0, 2, 0, 0, 0.1f, true, index++)));

	float time = clock() / CLOCKS_PER_SEC;

	std::string bmnames[4] = { "fight","finishhim","scorpionwins","subzerowins" };
	int k = 0;
	for (auto entry : *animators)
	{
		AnimationFilm* af = new AnimationFilm(*afh->GetFilm(bmnames[k]));

		Sprite *s = new Sprite(bmXs[k], bmYs[k], af, flipped);
		((FrameRangeAnimator*)entry.second)->Start(s, (FrameRangeAnimation*)animations.at(entry.first), time, true);

		AnimatorHolder::Register(entry.second);
		AnimatorHolder::MarkAsSuspended(animators->at(bmnames[k]));
		sprites->Add(s, 0);
	
		++k;
	}

}



