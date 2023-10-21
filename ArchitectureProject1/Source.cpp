#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include "Player.h"
#include "SDLControl.h"
#include "Asteroid.h"
#include "GameTime.h"
#include "EnemyShip.h"
#include "cmath"

#include <thread>

int main() 
{
	int playerLives = 3;
	int points = 0;
	Player* player = new Player();
	EnemyShip* enemy = new EnemyShip();

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

		player->Draw(renderer);

		
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