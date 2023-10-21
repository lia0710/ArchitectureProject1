#include "Enemy_Bullet.h"

#include "EnemyShip.h"

Enemy_Bullet::Enemy_Bullet(SDL_Renderer* _renderer)
{
	Enemy_Bullet::renderer = _renderer;
	Initialize(_renderer);
}

Enemy_Bullet::~Enemy_Bullet()
{
}

void Enemy_Bullet::Initialize(SDL_Renderer* _renderer)
{
	SDL_Surface* surface = IMG_Load("laserRed.png");
	SDL_Texture* itexture = SDL_CreateTextureFromSurface(_renderer, surface);
	texture = itexture;
	SDL_FreeSurface(surface);

	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);

	SDL_Rect dstrect = { 0, 0, size.x, size.y };
	enemyBulletRect = dstrect;
}

void Enemy_Bullet::Update()
{

}


void Enemy_Bullet::Draw(SDL_Renderer* drenderer)
{
	enemyBulletRect.x -= 1;
	SDL_RenderCopy(drenderer, texture, NULL, &enemyBulletRect);
	if (enemyBulletRect.x < -500)
	{
		Enemy_Bullet::~Enemy_Bullet();
	}
}