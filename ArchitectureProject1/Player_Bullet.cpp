#include "Player_Bullet.h"
#include "Player.h"

Player_Bullet::Player_Bullet(SDL_Renderer* _renderer)
{
	Player_Bullet::renderer = _renderer;
	Initialize(_renderer);
}

Player_Bullet::~Player_Bullet()
{
}

void Player_Bullet::Initialize(SDL_Renderer* _renderer)
{
	SDL_Surface* surface = IMG_Load("laserGreen.png");
	SDL_Texture* itexture = SDL_CreateTextureFromSurface(_renderer, surface);
	texture = itexture;
	SDL_FreeSurface(surface);

	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);

	SDL_Rect dstrect = { 0, 0, size.x, size.y };
	playerBulletRect = dstrect;
}

void Player_Bullet::Update()
{

}


void Player_Bullet::Draw(SDL_Renderer* drenderer)
{
	playerBulletRect.x += 1;
	SDL_RenderCopy(drenderer, texture, NULL, &playerBulletRect);
	if (playerBulletRect.x > 500)
	{
		Player_Bullet::~Player_Bullet();
	}
}