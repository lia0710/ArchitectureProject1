#pragma once

#ifndef _ENEMY
#define _ENEMY
#include "SDL.h"
#include "SDL_image.h"
#include "Enemy_Bullet.h"
#include "Player.h"
#include <vector>

class EnemyShip
{
public:
	SDL_Event event;
	SDL_Rect enemyRect;
	SDL_Texture* texture;
	SDL_Renderer* renderer;

	Player* player;

	//list of bullets
	//each time the player draws, iterate through the list and also call draw on the bullets
	//draw from the bullets will also move them
	std::vector<Enemy_Bullet*> bulletList;
	int index = 0;

	EnemyShip();
	~EnemyShip();
	void Initialize(SDL_Renderer* _renderer);
	void Update();
	void Move(Player* player);
	void Shoot(Player* player);
	void Draw(SDL_Renderer* _renderer);

};

#endif