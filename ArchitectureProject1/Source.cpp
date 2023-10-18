#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include "Player.h"
#include "SDLControl.h"

void keyControls()
{
	//have this get called if keydown event is triggered
	//check blackjack, see how I used keys with c++ there
	//paralax game. player is always "moving forward" (screen is scrolling)
	//player doesn't turn, always faces same direction, enemies cannot get behind
}

int main() 
{
	Player* player = new Player();

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	bool quit = false;

	//change size here
	window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	player->Initialize(renderer);

	while (!quit)
	{
		player->Update();
		SDL_Event event;

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
		//SDL_RenderCopy(renderer, texture, NULL, &player->playerRect);
		//Render Objects here

		SDL_RenderPresent(renderer);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}