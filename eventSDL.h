#ifndef	_EVENTSDL_H
#define _EVENTSDL_H
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "sdl_init.h"

using namespace std;

namespace sdl
{
	class event_sdl
	{
		private:
			SDL_Event	event;
			int		mouseX;
			int		mouseY;
		public:
				event_sdl();
			int	event_listen();
			int	event_click();
	};
}


#endif
