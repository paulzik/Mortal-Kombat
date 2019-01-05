#pragma once
#include <SDL.h>
#include <SDL_image.h>

#define BITMAP SDL_Texture
#define LOAD_BITMAP(renderer, path) IMG_LoadTexture(renderer, path)
#define GETBITMAPWIDTH (BITMAP* bm) (bm->w)
