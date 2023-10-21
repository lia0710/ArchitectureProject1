#include "Player.h"

Player::Player()
{
}

void Player::Initialize(SDL_Renderer* _renderer)
{
	renderer = _renderer;
	SDL_Surface* surface = IMG_Load("player.png");
	SDL_Texture* itexture = SDL_CreateTextureFromSurface(_renderer, surface);
	texture = itexture;
	SDL_FreeSurface(surface);

	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);

	SDL_Rect dstrect = { 100, 300, size.x*2, size.y*2 };

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
	if (pevent.key.keysym.sym == SDLK_SPACE)
	{
		Player_Bullet* bullet = new Player_Bullet(renderer);
		bulletList.push_back(bullet);
		bullet->playerBulletRect.x = playerRect.x + 70;
		bullet->playerBulletRect.y = playerRect.y + 40;
		index++;
	}
}

void Player::Draw(SDL_Renderer* drenderer)
{
	SDL_RenderCopy(drenderer, texture, NULL, &playerRect);
	if (index > 0)
	{
		for (int i = 0; i < index; i++)
		{
			if (bulletList[i]->playerBulletRect.x > 1500)
			{
				delete bulletList[i];
				bulletList.erase(bulletList.begin() + i);
				index--;
			}
		}
		
	}
	if (bulletList.size() > 0)
	{
		
		for (std::vector<Player_Bullet*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
		{
			(**it).Draw(drenderer);
		}
	}
	
}