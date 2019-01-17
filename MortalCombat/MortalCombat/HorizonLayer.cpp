#include "HorizonLayer.h"



bool HorizonLayer::ClippedEntirely(SDL_Rect& area, SDL_Rect& in, SDL_Rect* out)
{

}


void HorizonLayer::DisplayHorizon(SDL_Rect& vw, SDL_Rect& da) {
	
	for (int i = 0; i < TOTAL_HOBJECTS; ++i) {
		SDL_Rect clipRect;
		if (!ClippedEntirely(vw, hRects[i], &clipRect)) {
			Point at(clipRect.x - vw.x, clipRect.y - vw.y);
			clipRect.x -= hRects[i].x;
			clipRect.y -= hRects[i].y;
			SDL_RenderCopy(renderer, hObjects[i], &hRects[i], &at);
			//MaskedBlit(hObjects[i], clipRect, dest, at);
		}
	}
}


HorizonLayer::HorizonLayer(SDL_Renderer* _renderer)
{
	renderer = _renderer;
	hObjects[0] = LOAD_BITMAP(renderer, "./Bitmaps/h5.png");
	hObjects[1] = LOAD_BITMAP(renderer, "./Bitmaps/h4.png");
	hObjects[2] = LOAD_BITMAP(renderer, "./Bitmaps/h3.png");
	hObjects[3] = LOAD_BITMAP(renderer, "./Bitmaps/h2.png");
	hObjects[4] = LOAD_BITMAP(renderer, "./Bitmaps/h1.png");

	hRects[0].w = 400;	hRects[0].h = 132;
	hRects[1].w = 857;	hRects[1].h = 195;
	hRects[2].w = 792;	hRects[2].h = 61;
	hRects[3].w = 632;	hRects[3].h = 179;
	hRects[4].w = 1068;	hRects[4].h = 100;


}


HorizonLayer::~HorizonLayer()
{
}
