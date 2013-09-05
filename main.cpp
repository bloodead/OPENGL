#include "sdl_init.h"
#include "eventSDL.h"
#include "create_vertex.h"


int	main(int,char* [])
{
	float	width,height;
	width = 800.0f;
	height = 600.0f;

	sdl::createwin	openglWindow(800,600,"OPENGL 4.0 BLOODEAD");
	sdl::event_sdl	event;

	GLint	vs_id;
	GLint	fs_id;
	GLint	prog_id;
	GLuint	viewMatrixLocation;
	GLuint	projMatrixLocation;
	GLuint	vaoid,vboid,indexBufferId;	
	const	char*	fragmentShader = openglWindow.load("fragmentShader.glsl");
	 const   char*   vertexShader = openglWindow.load("vertexShader.glsl");



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


	
		std::cout << vertices[0].xyzw << std::endl;
		glGenVertexArrays(1, &vaoid);
		glBindVertexArray(vaoid);
		glGenBuffers(1, &vboid);
		glBindBuffer(GL_ARRAY_BUFFER, vboid);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(myopengl::vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(myopengl::vertex), (GLvoid*)sizeof(vertices[0].xyzw));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glGenBuffers(1,&indexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);
	//myopengl::vertexobj	cube_vertex(vertices,indices);

	vs_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs_id, 1, &vertexShader, nullptr);
	glCompileShader(vs_id);

	fs_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs_id, 1, &fragmentShader, nullptr);
	glCompileShader(fs_id);



	prog_id = glCreateProgram();
	glAttachShader(prog_id, vs_id);
	glAttachShader(prog_id, fs_id);
	glLinkProgram(prog_id);
	glUseProgram(prog_id);

	auto viewMatrix = glm::lookAt(glm::vec3(4.0f,3.0f,7.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
	viewMatrixLocation = glGetUniformLocation(prog_id,"viewMatrix");
	glUniformMatrix4fv(viewMatrixLocation,1,GL_FALSE,&viewMatrix[0][0]);

	auto projMatrix = glm::perspective(45.0f, width / height,0.1f,100.0f);
	projMatrixLocation = glGetUniformLocation(prog_id,"projMatrix");
	glUniformMatrix4fv(projMatrixLocation,1,GL_FALSE,&projMatrix[0][0]);






























	while (openglWindow.GetStatusProg())
	{
		if (event.event_listen() == 2)
			return 0;
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
		glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,nullptr);
	//	cube_vertex.vertexDraw();
		SDL_GL_SwapWindow(openglWindow.getMain());

	}

	return 0;
}
