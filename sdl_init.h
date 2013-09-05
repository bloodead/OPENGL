#ifndef _SDL_INIT_H_
#define _SDL_INIT_H_
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>



namespace sdl
{
	class createwin
	{
		private:
			SDL_Window*	MainWindow;
			SDL_GLContext	MainContext;
			int		progLife;
		public:
			createwin();
			~createwin();
			createwin(int w, int h, std::string title);
			void	refresh();
			int	error_videoDrivers();
			int	GetStatusProg();
			char*	load(const char* filename);
			SDL_Window*	getMain();
	};

}


#endif
