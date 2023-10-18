#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"

void keyControls()
{
	//have this get called if keydown event is triggered
	//check blackjack, see how I used keys with c++ there
	//paralax game. player is always "moving forward" (screen is scrolling)
	//player doesn't turn, always faces same direction, enemies cannot get behind
}

int main() 
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	bool quit = false;

	//change size here
	window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* surface = IMG_Load("player.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);

	SDL_Rect dstrect = { 0, 0, size.x, size.y };
	

	while (!quit)
	{
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
				dstrect.y -= 1;
			case SDL_KEYUP:
				//dstrect.y += 1;
				//break;
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEWHEEL:
				//std::cout << "Mouse Event" << std::endl;
				break;
			}
		}



		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		// Render Objects here

		SDL_RenderPresent(renderer);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}