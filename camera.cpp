#include "camera.h"

myopengl::camera::camera(GLint	prog_tmp)
{
	posX = 0.0f;
	posY = 0.0f;
	posZ = 0.0f;
	speed = 0.1f;
	prog_id = prog_tmp;
	viewMatrix = glm::lookAt(glm::vec3(4.0f,3.0f,7.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.1f));
	viewMatrixLocation = glGetUniformLocation(prog_id,"viewMatrix");
	glUniformMatrix4fv(viewMatrixLocation,1,GL_FALSE,&viewMatrix[0][0]);	
}



void	myopengl::camera::moveCamera(int sens)
{
std::cout << posY  << std::endl;	

		switch(sens)
		{
			case 10:
				posY = posY + speed;
				viewMatrix = glm::lookAt(glm::vec3(4.0f,3.0f,7.0f),glm::vec3(posX,posY,posZ),glm::vec3(0.0f,0.0f,0.1f));
				glUniformMatrix4fv(viewMatrixLocation,1,GL_FALSE,&viewMatrix[0][0]);
				break;
			case 11:
				posY = posY - speed;
				viewMatrix = glm::lookAt(glm::vec3(4.0f,3.0f,7.0f),glm::vec3(posX,posY,posZ),glm::vec3(0.0f,0.0f,0.1f));
				glUniformMatrix4fv(viewMatrixLocation,1,GL_FALSE,&viewMatrix[0][0]);
				break;
			case 13:
				posX = posX + speed;
				viewMatrix = glm::lookAt(glm::vec3(4.0f,3.0f,7.0f),glm::vec3(posX,posY,posZ),glm::vec3(0.0f,0.0f,0.1f));
				glUniformMatrix4fv(viewMatrixLocation,1,GL_FALSE,&viewMatrix[0][0]);
				break;
			case 12:
				posX = posX - speed;
				viewMatrix = glm::lookAt(glm::vec3(4.0f,3.0f,7.0f),glm::vec3(posX,posY,posZ),glm::vec3(0.0f,0.0f,0.1f));
				glUniformMatrix4fv(viewMatrixLocation,1,GL_FALSE,&viewMatrix[0][0]);
				break;

		}

}
