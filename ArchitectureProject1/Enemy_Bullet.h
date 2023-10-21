#pragma once
#ifndef _EnemyBullet
#define _EnemyBullet
#include "SDL.h"
#include "SDL_image.h"

class Enemy_Bullet
{
public:
	SDL_Event event;
	SDL_Rect enemyBulletRect;
	SDL_Texture* texture;
	SDL_Renderer* renderer;

	Enemy_Bullet(SDL_Renderer* _renderer);
	~Enemy_Bullet();
	void Initialize(SDL_Renderer* _renderer);
	void Update();
	void Draw(SDL_Renderer* _renderer);
};

#endif