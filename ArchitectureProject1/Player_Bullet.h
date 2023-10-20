#pragma once
#ifndef _PlayerBullet
#define _PlayerBullet
#include "SDL.h"
#include "SDL_image.h"

class Player_Bullet
{
public:
	SDL_Event event;
	SDL_Rect playerBulletRect;
	SDL_Texture* texture;
	SDL_Renderer* renderer;

	Player_Bullet(SDL_Renderer* _renderer);
	~Player_Bullet();
	void Initialize(SDL_Renderer* _renderer);
	void Update();
	void Draw(SDL_Renderer* _renderer);
};

#endif