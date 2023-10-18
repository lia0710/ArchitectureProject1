#pragma once
#ifndef _Player
#define _Player
#include "SDL.h"
#include "SDL_image.h"
class Player
{
public:
	SDL_Event event;
	SDL_Rect playerRect;
	SDL_Texture* texture; 
	SDL_Renderer* renderer;

	Player();
	~Player();
	void Initialize(SDL_Renderer* _renderer);
	void Update();
	void Move(SDL_Event pevent);
	void Draw(SDL_Renderer* _renderer);

};

#endif