#include "sdl_init.h"


using namespace std;

sdl::createwin::createwin(int w, int h,string title)
{
	char * buffer = new char[title.length()+1];
	strcpy(buffer,title.c_str());

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	error_videoDrivers();
	MainWindow = SDL_CreateWindow(buffer, 0, 0, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	MainContext = SDL_GL_CreateContext(MainWindow);
	SDL_GL_SetSwapInterval(1);
	progLife = 1;
	glewInit();
	if (nullptr == MainContext)
		std::cerr << "[ERROR] Cannot create context" << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


}


int sdl::createwin::error_videoDrivers()
{
	auto    count = SDL_GetNumVideoDrivers();
	if (count == 0)
		return EXIT_FAILURE;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for(auto i=0; i < count; ++i)
		std::cout << SDL_GetVideoDriver(i) << std::endl;

	return 0;
}

SDL_Window*	sdl::createwin::getMain()
{
	return MainWindow;
}

char*	sdl::createwin::load(const char*	filename)
{
	std::ifstream   file(filename, std::ios::binary);
	std::streampos  len;
	char*           buffer;

	file.seekg(0, std::ios::end);
	len = file.tellg();
	file.seekg(0, std::ios::beg);
	buffer = new char[(int)len + 1];
	file.read(buffer, len);
	buffer[len] = '\0';
	return buffer;
}

  
sdl::createwin::createwin()
{
	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	error_videoDrivers();
	MainWindow = SDL_CreateWindow("OPENGL DEFAULT", 0, 0, 800, 680, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	MainContext = SDL_GL_CreateContext(MainWindow);
	SDL_GL_SetSwapInterval(1);
	progLife = 1;
	glewInit();
	if (nullptr == MainContext)
		std::cerr << "[ERROR] Cannot create context" << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}


int	sdl::createwin::GetStatusProg()
{
	return progLife;
}

sdl::createwin::~createwin()
{
	
}


void sdl::createwin::refresh()
{

}


