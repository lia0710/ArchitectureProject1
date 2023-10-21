#include "EnemyShip2.h"
#include <iostream>

EnemyShip2::EnemyShip2()
{
}

EnemyShip2::~EnemyShip2()
{

}

void EnemyShip2::Initialize(SDL_Renderer* _renderer)
{
	renderer = _renderer;
	SDL_Surface* surface = IMG_Load("enemyUFO.png");
	SDL_Texture* itexture = SDL_CreateTextureFromSurface(_renderer, surface);
	texture = itexture;
	SDL_FreeSurface(surface);

	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);

	SDL_Rect dstrect = { 1500, 300, size.x * 2, size.y * 2 };

	enemyRect = dstrect;
}

void EnemyShip2::Update()
{

}

void EnemyShip2::Move(Player* player)
{
	if (enemyRect.x > 1000)
	{
		enemyRect.x -= 100;
	}
	if (enemyRect.y > player->playerRect.y)
	{
		enemyRect.y -= 5;
	}
	if (enemyRect.y < player->playerRect.y)
	{
		enemyRect.y += 5;
	}
}

void EnemyShip2::Shoot(Player* player)
{
	if ((enemyRect.x <= 1000) && (enemyRect.y < player->playerRect.y + 64) && (enemyRect.y > player->playerRect.y - 64))
	{
		Enemy_Bullet* bullet = new Enemy_Bullet(renderer);
		bulletList.push_back(bullet);
		bullet->enemyBulletRect.x = enemyRect.x - 70;
		bullet->enemyBulletRect.y = enemyRect.y + 40;
		index++;
	}
}

void EnemyShip2::Draw(SDL_Renderer* drenderer)
{
	SDL_RenderCopy(drenderer, texture, NULL, &enemyRect);
	if (index > 0)
	{
		for (int i = 0; i < index; i++)
		{
			if (bulletList[i]->enemyBulletRect.x > 1500)
			{
				delete bulletList[i];
				bulletList.erase(bulletList.begin() + i);
				index--;
			}
		}

	}
	if (bulletList.size() > 0)
	{

		for (std::vector<Enemy_Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
		{
			(**it).Draw(drenderer);
		}
	}

}