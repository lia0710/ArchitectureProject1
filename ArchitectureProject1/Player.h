#pragma once
#ifndef _Player
#define _Player
#include "SDL.h"
#include "SDL_image.h"
#include "Player_Bullet.h"
#include <vector>

class Player
{
public:
	SDL_Event event;
	SDL_Rect playerRect;
	SDL_Texture* texture; 
	SDL_Renderer* renderer;

	//list of bullets
	//each time the player draws, iterate through the list and also call draw on the bullets
	//draw from the bullets will also move them
	std::vector<Player_Bullet*> bulletList;
	int index = 0;

	Player();
	~Player();
	void Initialize(SDL_Renderer* _renderer);
	void Update();
	void Move(SDL_Event pevent);
	void Draw(SDL_Renderer* _renderer);

};

#endif