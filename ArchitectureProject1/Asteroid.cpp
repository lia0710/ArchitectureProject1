#include "Asteroid.h"
#include "Player.h"
#include "RandomNumber.h"
#include <iostream>

Asteroid::Asteroid(SDL_Renderer* _renderer)
{
	Asteroid::renderer = _renderer;
	Initialize(_renderer);
}

Asteroid::~Asteroid()
{
}



void Asteroid::Initialize(SDL_Renderer* _renderer)
{
	RandomNumber* newrandom = new RandomNumber();
	int random = newrandom->GetRandomNumber(0, 1);
	SDL_Surface* surface;
	if (random == 0)
	{
		surface = IMG_Load("meteorBig.png");
	}
	else
	{
		surface = IMG_Load("meteorSmall.png");
	}
	SDL_Texture* itexture = SDL_CreateTextureFromSurface(_renderer, surface);
	texture = itexture;
	SDL_FreeSurface(surface);

	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);

	random = newrandom->GetRandomNumber(0, 500);
	SDL_Rect dstrect = { 1000, random, size.x, size.y};
	asteroidRect = dstrect;
}

void Asteroid::Update()
{

}


void Asteroid::Draw(SDL_Renderer* drenderer)
{
	asteroidRect.x -= 1;
	SDL_RenderCopy(drenderer, texture, NULL, &asteroidRect);
	if (asteroidRect.x < -100)
	{
		Asteroid::~Asteroid();
	}
}

