#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Player.h"
#include "SDLControl.h"
#include "Asteroid.h"
#include "GameTime.h"
#include "EnemyShip.h"
#include "EnemyShip2.h"
#include "cmath"

#include <thread>

int main() 
{
	int playerLives = 3;
	int points = 0;
	Player* player = new Player();
	EnemyShip* enemy = new EnemyShip();
	EnemyShip2* enemy2 = new EnemyShip2();

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	float timecount = 3.0f;
	float movecount = 0.1f;
	float shootcount = 1;

	std::vector<Asteroid*> asteroidList;
	int asteroidIndex = 0;

	std::vector<EnemyShip*> enemyList;
	int enemyIndex = 0;

	bool quit = false;

	//change size here
	window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//background, uses three of the same image scrolling on a loop

	SDL_Surface* surface1 = IMG_Load("starBackground.png");
	SDL_Surface* surface2 = IMG_Load("starBackground.png");
	SDL_Surface* surface3 = IMG_Load("starBackground.png");
	SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
	SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, surface3);
	SDL_FreeSurface(surface1);
	SDL_FreeSurface(surface2);
	SDL_FreeSurface(surface3);

	SDL_Point size1;
	SDL_Point size2;
	SDL_Point size3;
	SDL_QueryTexture(texture1, NULL, NULL, &size1.x, &size1.y);
	SDL_QueryTexture(texture2, NULL, NULL, &size2.x, &size2.y);
	SDL_QueryTexture(texture3, NULL, NULL, &size3.x, &size3.y);

	SDL_Rect dstrect1 = { -1280, 0, 1280, 720};
	SDL_Rect dstrect2 = { 0, 0, 1280, 720 };
	SDL_Rect dstrect3 = { 1280, 0, 1280, 720 };

	//background

	//lives

	SDL_Surface* surfacelife1 = IMG_Load("life.png");
	SDL_Surface* surfacelife2 = IMG_Load("life.png");
	SDL_Surface* surfacelife3 = IMG_Load("life.png");
	SDL_Texture* texturelife1 = SDL_CreateTextureFromSurface(renderer, surfacelife1);
	SDL_Texture* texturelife2 = SDL_CreateTextureFromSurface(renderer, surfacelife2);
	SDL_Texture* texturelife3 = SDL_CreateTextureFromSurface(renderer, surfacelife3);
	SDL_FreeSurface(surfacelife1);
	SDL_FreeSurface(surfacelife2);
	SDL_FreeSurface(surfacelife3);

	SDL_Point sizelife1;
	SDL_Point sizelife2;
	SDL_Point sizelife3;
	SDL_QueryTexture(texturelife1, NULL, NULL, &sizelife1.x, &sizelife1.y);
	SDL_QueryTexture(texturelife2, NULL, NULL, &sizelife2.x, &sizelife2.y);
	SDL_QueryTexture(texturelife3, NULL, NULL, &sizelife3.x, &sizelife3.y);

	SDL_Rect dstrectlife1 = { 0, 0, sizelife1.x, sizelife1.y };
	SDL_Rect dstrectlife2 = { 50, 0, sizelife2.x, sizelife2.y };
	SDL_Rect dstrectlife3 = { 100, 0, sizelife3.x, sizelife3.y };

	//lives

	//score text

	TTF_Font* cour = TTF_OpenFont("cour.ttf", 36);
	SDL_Color black = { 255, 255, 255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(cour, "Score:", black);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	SDL_Point sizetext;
	SDL_QueryTexture(Message, NULL, NULL, &sizetext.x, &sizetext.y);
	SDL_Rect dstrecttext = { 0, 0, sizetext.x, sizetext.y };

	//score text

	player->Initialize(renderer);


	while (!quit)
	{
		//enemy dead, spawn new enemy
		if (enemyIndex == 0)
		{
			enemy = new EnemyShip();
			enemy->Initialize(renderer);
			enemyList.push_back(enemy);
			enemyIndex++;
		}

		player->Update();
		enemy->Update();
		SDL_Event event;

		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		GameTime::Instance().Update();

		if (GameTime::Instance().TotalTime() > timecount)
		{
			timecount += 3;
			Asteroid* asteroid = new Asteroid(renderer);
			asteroidList.push_back(asteroid);
			asteroidIndex++;
		}

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					quit = true;
				}
				break;
			case SDL_KEYDOWN:
				player->Move(event);
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}
			case SDL_KEYUP:
				break;
			}
		}

		if (GameTime::Instance().TotalTime() > movecount)
		{
			movecount += 0.1f;
			enemy->Move(player);
		}
		if (GameTime::Instance().TotalTime() > shootcount)
		{
			shootcount += 1;
			enemy->Shoot(player);
		}


		SDL_RenderClear(renderer);
		
		//background draw and animate
		dstrect1.x -= 1;
		dstrect2.x -= 1;
		dstrect3.x -= 1;
		if (dstrect1.x <= -1280)
		{
			dstrect1.x = 1280;
		}
		if (dstrect2.x <= -1280)
		{
			dstrect2.x = 1280;
		}
		if (dstrect3.x <= -1280)
		{
			dstrect3.x = 1280;
		}
		SDL_RenderCopy(renderer, texture1, NULL, &dstrect1);
		SDL_RenderCopy(renderer, texture2, NULL, &dstrect2);
		SDL_RenderCopy(renderer, texture3, NULL, &dstrect3);

		player->Draw(renderer);

		//life draw
		if (playerLives >= 3)
		{
			SDL_RenderCopy(renderer, texturelife3, NULL, &dstrectlife3);
		}
		if (playerLives >= 2)
		{
			SDL_RenderCopy(renderer, texturelife2, NULL, &dstrectlife2);
		}
		if (playerLives >= 1)
		{
			SDL_RenderCopy(renderer, texturelife1, NULL, &dstrectlife1);
		}

		//score draw
		SDL_RenderCopy(renderer, Message, NULL, &dstrecttext);



		
		if (asteroidIndex > 0)
		{
			for (int i = 0; i < asteroidIndex; i++)
			{
				asteroidList[i]->Draw(renderer); 

				//player to asteroid collision calc
				int distancex = (player->playerRect.x + (player->playerRect.w / 2)) - (asteroidList[i]->asteroidRect.x + (asteroidList[i]->asteroidRect.w) / 2);
				distancex = distancex * distancex;
				int distancey = (player->playerRect.y + (player->playerRect.h) / 2) - (asteroidList[i]->asteroidRect.y + (asteroidList[i]->asteroidRect.h) / 2);
				distancey = distancey * distancey;
				float distance = (float)(distancey + distancex);
				distance = sqrtf(distance);

				bool asteroiddelete = false;
				for (int j = 0; j < player->index; j++)
				{
					//bullet to asteroid collision calc
					if (asteroiddelete != true)
					{
						int bdistancex = (player->bulletList[j]->playerBulletRect.x + (player->bulletList[j]->playerBulletRect.w / 2)) - (asteroidList[i]->asteroidRect.x + (asteroidList[i]->asteroidRect.w) / 2);
						bdistancex = bdistancex * bdistancex;
						int bdistancey = (player->bulletList[j]->playerBulletRect.y + (player->bulletList[j]->playerBulletRect.h / 2)) - (asteroidList[i]->asteroidRect.y + (asteroidList[i]->asteroidRect.h) / 2);
						bdistancey = bdistancey * bdistancey;
						float bdistance = (float)(bdistancey + bdistancex);
						bdistance = sqrtf(bdistance);
						if (asteroiddelete == false)
						{
							if (bdistance - player->bulletList[j]->playerBulletRect.w / 2 - asteroidList[i]->asteroidRect.w / 2 < 0)
							{
								delete asteroidList[i];
								asteroidList.erase(asteroidList.begin() + i);
								asteroidIndex--;
								asteroiddelete = true;
								points++;
							}
						}
					}
					
				}

				if (asteroiddelete == false)
				{
					if (distance - player->playerRect.w / 2 - asteroidList[i]->asteroidRect.w / 2 < 0)
					{
						playerLives--;
						delete asteroidList[i];
						asteroidList.erase(asteroidList.begin() + i);
						asteroidIndex--;
					}
					else if (asteroidList[i]->asteroidRect.x < -100)
					{
						delete asteroidList[i];
						asteroidList.erase(asteroidList.begin() + i);
						asteroidIndex--;
					}
				}
				

				//collision
				//player = 96x96
				//asteroid = 64x64 or 22x21
			}
		}
		






		

		//enemy ship collision
		if (enemyIndex > 0)
		{
			for (int i = 0; i < enemyIndex; i++)
			{
				enemyList[i]->Draw(renderer);
				
				//player to enemy ship collision calc
				int distancex = (player->playerRect.x + (player->playerRect.w / 2)) - (enemyList[i]->enemyRect.x + (enemyList[i]->enemyRect.w) / 2);
				distancex = distancex * distancex;
				int distancey = (player->playerRect.y + (player->playerRect.h) / 2) - (enemyList[i]->enemyRect.y + (enemyList[i]->enemyRect.h) / 2);
				distancey = distancey * distancey;
				float distance = (float)(distancey + distancex);
				distance = sqrtf(distance);

				bool enemydelete = false;

				for (int j = 0; j < player->index; j++)
				{
					if (enemydelete != true)
					{
						//bullet to enemy collision calc
						int bdistancex = (player->bulletList[j]->playerBulletRect.x + (player->bulletList[j]->playerBulletRect.w / 2)) - (enemyList[i]->enemyRect.x + (enemyList[i]->enemyRect.w) / 2);
						bdistancex = bdistancex * bdistancex;
						int bdistancey = (player->bulletList[j]->playerBulletRect.y + (player->bulletList[j]->playerBulletRect.h / 2)) - (enemyList[i]->enemyRect.y + (enemyList[i]->enemyRect.h) / 2);
						bdistancey = bdistancey * bdistancey;
						float bdistance = (float)(bdistancey + bdistancex);
						bdistance = sqrtf(bdistance);
						if (enemydelete == false)
						{
							if (bdistance - player->bulletList[j]->playerBulletRect.w / 2 - enemyList[i]->enemyRect.w / 2 < 0)
							{
								//enemy is hit. Deal damage here
								delete enemyList[i];
								enemyList.erase(enemyList.begin() + i);
								enemyIndex--;
								enemydelete = true;
								points = points + 3;
							}
						}
					}
					
				}

				//enemy bullet to player collision
				for (int j = 0; j < enemy->index; j++)
				{
					//bullet to enemy collision calc
					int bdistancex = (enemy->bulletList[j]->enemyBulletRect.x + (enemy->bulletList[j]->enemyBulletRect.w / 2)) - (player->playerRect.x + (player->playerRect.w) / 2);
					bdistancex = bdistancex * bdistancex;
					int bdistancey = (enemy->bulletList[j]->enemyBulletRect.y + (enemy->bulletList[j]->enemyBulletRect.h / 2)) - (player->playerRect.y + (player->playerRect.h) / 2);
					bdistancey = bdistancey * bdistancey;
					float bdistance = (float)(bdistancey + bdistancex);
					bdistance = sqrtf(bdistance);
					if (bdistance - enemy->bulletList[j]->enemyBulletRect.w / 2 - player->playerRect.w / 2 < 0)
					{
						playerLives--;
						delete enemy->bulletList[j];
						enemy->bulletList.erase(enemy->bulletList.begin() + j);
						enemy->index--;
					}
				}

				//player enemy collision
				if (enemydelete == false)
				{
					if (distance - player->playerRect.w / 2 - enemyList[i]->enemyRect.w / 2 < 0)
					{
						//enemy to player crash, make player lose a life
						playerLives--;
						delete enemyList[i];
						enemyList.erase(enemyList.begin() + i);
						enemyIndex--;
						points = points + 3;
					}
				}
			}
		}
		



		//Render Objects here

		SDL_RenderPresent(renderer);
		if (playerLives <= 0)
		{
			quit = true;
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}