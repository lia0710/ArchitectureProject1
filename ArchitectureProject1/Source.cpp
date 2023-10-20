#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include "Player.h"
#include "SDLControl.h"
#include "Asteroid.h"
#include "GameTime.h"

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

		//use player draw()
		//player->texture = texture;
		player->Draw(renderer);
		if (asteroidIndex > 0)
		{
			for (int i = 0; i < asteroidIndex; i++)
			{
				asteroidList[i]->Draw(renderer); 
				if (asteroidList[i]->asteroidRect.x < -100)
				{
					delete asteroidList[i];
					asteroidList.erase(asteroidList.begin() + i);
					asteroidIndex--;
				}

				//collision
				int distance = player->playerRect.x;

				//collision
			}
		}



		//Render Objects here

		SDL_RenderPresent(renderer);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}