#include "eventSDL.h"

int sdl::event_sdl::event_listen()
{		
	//	SDL_WaitEvent(&event);
	//	SDL_Delay(10);
	SDL_PollEvent(&event);

		switch(event.type)
		{
			case SDL_QUIT:
				return 2;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_UP)
					return 10;
				if (event.key.keysym.sym == SDLK_DOWN)
					return 11;
				if (event.key.keysym.sym == SDLK_LEFT)
					return 12;
				if (event.key.keysym.sym == SDLK_RIGHT)
					return 13;
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    return 8;
		}
	
	return 0;
}


int sdl::event_sdl::event_click()
{
	SDL_WaitEvent(&event);
	switch(event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			switch(event.button.button)
			{
				case SDL_BUTTON_LEFT:
					return 1;
			}
	}
	return 0;
	
}


sdl::event_sdl::event_sdl()
{

}


