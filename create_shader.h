#ifndef	_CREATE_SHADER_H_
#define _CREATE_SHADER_H_
#include <iostream>
#include <GL/glew.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace myopengl
{
	class	shader
	{
		private:
			GLint	vs_id;
			GLint	fs_id;
			GLint	prog_id;
			const	char*	fragmentShader;
			const	char*	vertexShader;
			glm::mat4	projMatrix;
			GLuint  projMatrixLocation;
			
		public:
			shader(const char* fShader, const char* vShader);
			void setModCamera();
			GLint	getProg();
	};

}


#endif
