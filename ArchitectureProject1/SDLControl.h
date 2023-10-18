#pragma once
#include "SDL.h"
#include "SDL_image.h"
#ifndef _SDLControl
#define _SDLControl

class SDLControl
{

public:
	SDLControl();
	~SDLControl();

	void Initialize();
	void Update();

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect playerRect;
	SDL_Texture* texture;


};

#endif