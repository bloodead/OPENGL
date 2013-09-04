#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <fstream>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

	float width = 500;
	float height = 500;


char*	load(const char* filename)
{
	std::ifstream	file(filename, std::ios::binary);
	std::streampos	len;
	char*		buffer;

	file.seekg(0, std::ios::end);
	len = file.tellg();
	file.seekg(0, std::ios::beg);
	buffer = new char[(int)len + 1];
	file.read(buffer, len);
	buffer[len] = '\0';
	return buffer;
}

int	main(int, char *[])
{
	// Check des returns values *
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // *
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0); // *
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); // *
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // *
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // *
	auto	count = SDL_GetNumVideoDrivers();

	if (0 == count)
		return EXIT_FAILURE;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (auto i = 0; i < count; ++i)
		std::cout << SDL_GetVideoDriver(i) << std::endl;

	auto	mainWindow = SDL_CreateWindow("OpenGL", 0, 0, 500, 500, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN); // *
	auto	mainContext = SDL_GL_CreateContext(mainWindow); // *
	auto	alive = true;
	const	char*	fragmentShader = load("fragmentShader.glsl");
	const	char*	vertexShader = load("vertexShader.glsl");
	GLuint	vaoid;
	GLuint	vboid;
	GLuint	indexBufferId[2];
	GLint	vs_id;
	GLint	fs_id;
	GLint	prog_id;
	GLuint	modelMatrixLocation;
	GLuint	modelMatrixLocation2;
	GLuint	viewMatrixLocation;
	GLuint	projMatrixLocation;
	float	dist;
	//GLuint	rotateMatrixLocation;


	dist = 1.0f;
	
	SDL_GL_SetSwapInterval(1); // *
	glewInit(); // * == GLEW_OK

	if (nullptr == mainContext)
	{
		std::cerr << "[ERROR] Cannot create context" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	struct vertex
	{
		GLfloat xyzw[4];
		GLfloat rgba[4];
	};

	vertex	vertices[] =
	{
		{{-1.0f,-1.0f,-1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},
		{{-1.0f,1.0f,-1.0f,1.0f},{0.0f,1.0f,0.0f,1.0f}},
		{{1.0f,-1.0f,-1.0f,1.0f},{0.0f,0.0f,1.0f,1.0f}},
		{{1.0f,1.0f,-1.0f,1.0f},{0.0f,1.0f,1.0f,1.0f}},
		{{-1.0f,-1.0f,1.0f,1.0f},{1.0f,0.0f,0.0f,1.0f}},
		{{-1.0f,1.0f,1.0f,1.0f},{0.0f,0.0f,1.0f,1.0f}},
		{{1.0f,-1.0f,1.0f,1.0f},{0.0f,1.0f,0.0f,1.0f}},
		{{1.0f,1.0f,1.0f,1.0f},{0.0f,1.0f,1.0f,1.0f}}
		
	};


	GLubyte	indices[]={
		0,1,3,
		0,3,2,
		3,1,4,
		3,4,2,
		0,5,7,
		0,7,6,
		7,5,8,
		7,8,6,
		0,9,11,
		0,11,10,
		11,9,12,
		11,12,10,
		0,13,15,
		0,15,14,
		15,13,16,
		15,16,14};

	GLubyte	alternateIndices[] = {
		0,1,2,3,6,7,4,5,0,1,5,7,1,3,6,4,2,0
		};


	glGenVertexArrays(1, &vaoid); // * check vaoid
	glBindVertexArray(vaoid);



	glGenBuffers(1, &vboid); // * check vboid
	glBindBuffer(GL_ARRAY_BUFFER, vboid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)sizeof(vertices[0].xyzw));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(2,indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferId[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferId[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(alternateIndices), alternateIndices,GL_STATIC_DRAW);

	vs_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs_id, 1, &vertexShader, nullptr); // ()
	glCompileShader(vs_id);
	GLchar* buffer;
	GLsizei length = 0;
	glGetShaderiv(vs_id, GL_INFO_LOG_LENGTH, &length);
	buffer = new GLchar[length+1];
	glGetShaderInfoLog(vs_id, length, &length, buffer);
	buffer[length] = '\0';
	std::cout << buffer <<std::endl;
	delete buffer;

	std::cout << std::endl << "----------------" << std::endl;

	fs_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs_id, 1, &fragmentShader, nullptr); // ()
	glCompileShader(fs_id);
	glGetShaderiv(fs_id, GL_INFO_LOG_LENGTH, &length);
	buffer = new GLchar[length+1];
	glGetShaderInfoLog(fs_id, length, &length, buffer);
	buffer[length] = '\0';
	std::cout << buffer <<std::endl;
	delete buffer;

	prog_id = glCreateProgram();
	glAttachShader(prog_id, vs_id);
	glAttachShader(prog_id, fs_id);
	glLinkProgram(prog_id);
	glUseProgram(prog_id);

	auto matrice_translate = glm::translate(glm::mat4(1.0f),glm::vec3(dist,0.0f,1.0f));
	modelMatrixLocation = glGetUniformLocation(prog_id,"modelMatrix");
	glUniformMatrix4fv(modelMatrixLocation,1,GL_FALSE,&matrice_translate[0][0]);
	//glEnableVertexAttribArray(modelMatrixLocation);
	auto matrice_translate2 = glm::translate(glm::mat4(1.0f),glm::vec3(0.1f,0.2f,0.6f));
	modelMatrixLocation2 = glGetUniformLocation(prog_id,"modelMatrix2");
	glUniformMatrix4fv(modelMatrixLocation2,1,GL_FALSE,&matrice_translate2[0][0]);

	//auto matrice_rotate = glm::rotate(glm::mat4(1.0f),45,glm::vec3(0.0f,0.0f,0.5f));
	//rotateMatrixLocation = glGetUniformLocation(prog_id,"rotateMatrix");
	//glUniformMatrix4fv(rotateMatrixLocation,1,GL_FALSE,&matrice_rotate[0][0]);
	//glEnableVertexAttribArray(rotateMatrixLocation);

	auto viewMatrix = glm::lookAt(glm::vec3(4.0f,3.0f,3.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
	viewMatrixLocation = glGetUniformLocation(prog_id,"viewMatrix");
	glUniformMatrix4fv(viewMatrixLocation,1,GL_FALSE,&viewMatrix[0][0]);
	//glEnableVertexAttribArray(viewMatrixLocation);
	
	auto projMatrix = glm::perspective(45.0f, width / height,0.1f,100.0f);
	projMatrixLocation = glGetUniformLocation(prog_id,"projMatrix");
	glUniformMatrix4fv(projMatrixLocation,1,GL_FALSE,&projMatrix[0][0]);
	//glEnableVertexAttribArray(projMatrixLocation);
	

	while (true == alive)
	{
		SDL_Event	ev;

		while (true == SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
				alive = false;
			if (ev.type == SDL_KEYDOWN)
			{
				if (ev.key.keysym.sym == SDLK_r)
				{
					//glEnable(GL_DEPTH_TEST);
					//glDepthFunc(GL_LESS);
					glEnable(GL_CULL_FACE);
					glFrontFace(GL_CW);
					glCullFace(GL_BACK);

				}
				if (ev.key.keysym.sym == SDLK_g)
				{
					dist = dist + 0.1f;
					matrice_translate = glm::translate(glm::mat4(1.0f),glm::vec3(dist,0.0f,0.5f));
					glUniformMatrix4fv(modelMatrixLocation,1,GL_FALSE,&matrice_translate[0][0]);
					glDrawElements(GL_TRIANGLES,1,GL_UNSIGNED_BYTE,nullptr);


				}
				if (ev.key.keysym.sym == SDLK_b)
					{
					dist = dist - 0.1f;
					matrice_translate = glm::translate(glm::mat4(1.0f),glm::vec3(dist,0.0f,0.5f));
					glUniformMatrix4fv(modelMatrixLocation,1,GL_FALSE,&matrice_translate[0][0]);
					glDrawElements(GL_TRIANGLES,1,GL_UNSIGNED_BYTE,nullptr);
					}
				if (ev.key.keysym.sym == SDLK_ESCAPE)
					alive = false;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		//glClearDepth(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
		glDrawElements(GL_TRIANGLES,38,GL_UNSIGNED_BYTE,nullptr);
		SDL_GL_SwapWindow(mainWindow);
	}

	SDL_GL_DeleteContext(mainContext);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
	return EXIT_SUCCESS;
}

