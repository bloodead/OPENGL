#include "sdl_init.h"
#include "eventSDL.h"
#include "create_vertex.h"
#include "create_shader.h"
#include "camera.h"

int	main(int,char* [])
{
	sdl::createwin	openglWindow(800,600,"OPENGL 4.0 BLOODEAD");
	sdl::event_sdl	event;

	myopengl::vertex	vertices[] =
	{
		{{-1.0f,1.0f,-1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},
		{{-1.0f,-1.0f,-1.0f,1.0f},{0.0f,1.0f,0.0f,1.0f}},
		{{-1.0f,1.0f,1.0f,1.0f},{0.0f,0.0f,1.0f,1.0f}},
		{{-1.0f,-1.0f,1.0f,1.0f},{0.0f,1.0f,1.0f,1.0f}},
		{{1.0f,1.0f,1.0f,1.0f},{1.0f,0.0f,0.0f,1.0f}},
		{{1.0f,-1.0f,1.0f,1.0f},{0.0f,0.0f,1.0f,1.0f}},
		{{1.0f,1.0f,-1.0f,1.0f},{0.0f,1.0f,0.0f,1.0f}},
		{{1.0f,-1.0f,-1.0f,1.0f},{0.0f,1.0f,1.0f,1.0f}}
	};

	GLubyte	indices[] = {
		0,1,2,2,1,3,4,5,6,6,5,7,3,1,5,5,1,7,0,2,6,6,2,4,6,7,0,0,7,1,2,3,4,4,3,5
		};


	
	myopengl::vertexobj	cube_vertex(vertices,indices,sizeof(vertices),sizeof(indices));
	myopengl::shader	shaderBasic(openglWindow.load("fragmentShader.glsl"),openglWindow.load("vertexShader.glsl"));
	myopengl::camera	camera(shaderBasic.getProg());	
	
	shaderBasic.setModCamera();



	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	while (openglWindow.GetStatusProg())
	{
		if (event.event_listen() == 2)
			return 0;
		camera.moveCamera(event.event_listen());
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,nullptr);
		SDL_GL_SwapWindow(openglWindow.getMain());

	}

	return 0;
}
