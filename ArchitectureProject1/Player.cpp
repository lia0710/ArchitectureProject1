#include "Player.h"
#include <iostream>

Player::Player()
{
}

void Player::Initialize(SDL_Renderer* _renderer)
{
	SDL_Surface* surface = IMG_Load("player.png");
	SDL_Texture* itexture = SDL_CreateTextureFromSurface(_renderer, surface);
	texture = itexture;
	SDL_FreeSurface(surface);

	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);

	SDL_Rect dstrect = { 0, 0, size.x, size.y };
	playerRect = dstrect;
}

void Player::Update()
{
	
}

void Player::Move(SDL_Event pevent)
{
	if (pevent.key.keysym.sym == SDLK_w)
	{
		playerRect.y -= 10;
	}
	if (pevent.key.keysym.sym == SDLK_a)
	{
		playerRect.x -= 10;
	}
	if (pevent.key.keysym.sym == SDLK_s)
	{
		playerRect.y += 10;
	}
	if (pevent.key.keysym.sym == SDLK_d)
	{
		playerRect.x += 10;
	}
}

void Player::Draw(SDL_Renderer* drenderer)
{
	SDL_RenderCopy(drenderer, texture, NULL, &playerRect);
}