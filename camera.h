#ifndef _CAMERA_H_
#define _CEMERA_H_
#include <iostream>
#include <GL/glew.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace myopengl
{

	class camera
	{
		private:
			float	posX;
			float	posY;
			float	posZ;
			float	speed;
			GLint	prog_id;
			glm::mat4	viewMatrix;
			GLuint  viewMatrixLocation;

		public:
			camera(GLint	progtmp);
			void	moveCamera(int	sens);
	};

}

#endif
