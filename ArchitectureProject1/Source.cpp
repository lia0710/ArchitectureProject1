#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include "Player.h"
#include "SDLControl.h"
#include "Asteroid.h"
#include "GameTime.h"
#include "cmath"

#include <thread>

int main() 
{
	Player* player = new Player();

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	float timecount = 3.0f;

	std::vector<Asteroid*> asteroidList;
	int asteroidIndex = 0;

	bool quit = false;

	//change size here
	window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	player->Initialize(renderer);

	//std::cout << "x: " << player->playerRect.x << std::endl;
	//std::cout << "y: " << player->playerRect.y << std::endl;
	//std::cout << "width: " << player->playerRect.w << std::endl;
	//std::cout << "height: " << player->playerRect.h << std::endl;

	while (!quit)
	{
		player->Update();
		SDL_Event event;

		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		GameTime::Instance().Update();

		if (GameTime::Instance().TotalTime() > timecount)
		{
			timecount += 3;
			Asteroid* asteroid = new Asteroid(renderer);
			asteroidList.push_back(asteroid);
			asteroidIndex++;

			//std::cout << "x: " << asteroid->asteroidRect.x << std::endl;
			//std::cout << "y: " << asteroid->asteroidRect.y << std::endl;
			//std::cout << "width: " << asteroid->asteroidRect.w << std::endl;
			//std::cout << "height: " << asteroid->asteroidRect.h << std::endl;
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
			case SDL_KEYUP:
				break;
			}
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
				//bullet to asteroid collision calc
				for (int j = 0; j < player->index; j++)
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
						}
					}
				}

				if (asteroiddelete == false)
				{
					if (distance - player->playerRect.w / 2 - asteroidList[i]->asteroidRect.w / 2 < 0)
					{
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
				

				//collision
				//player = 96x96
				//asteroid = 64x64 or 22x21
			}
		}



		//Render Objects here

		SDL_RenderPresent(renderer);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}