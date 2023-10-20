#pragma once
#ifndef _Asteroid
#define _Asteroid
#include "SDL.h"
#include "SDL_image.h"

class Asteroid
{
public:
	SDL_Event event;
	SDL_Rect asteroidRect;
	SDL_Texture* texture;
	SDL_Renderer* renderer;

	Asteroid(SDL_Renderer* _renderer);
	~Asteroid();
	void Initialize(SDL_Renderer* _renderer);
	void Update();
	void Draw(SDL_Renderer* _renderer);
};

#endif