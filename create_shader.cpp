#include "create_shader.h"



myopengl::shader::shader(const char*	fShader, const char* vShader)
{
	int infologLength = 0;
	int maxLength;

	fragmentShader = fShader;
	vertexShader = vShader;

	vs_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs_id, 1, &vertexShader, nullptr);
	glCompileShader(vs_id);
	
	fs_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs_id, 1, &fragmentShader, nullptr);
	glCompileShader(fs_id);

	prog_id = glCreateProgram();
	if (prog_id == 0)
		std::cout << "PROG ID ERROR " << std::endl;
	glAttachShader(prog_id, vs_id);
	glAttachShader(prog_id, fs_id);
	glLinkProgram(prog_id);
	glGetProgramiv(prog_id,GL_INFO_LOG_LENGTH,&maxLength);
	char infoLog[maxLength];
	glGetProgramInfoLog(prog_id, maxLength, &infologLength, infoLog);
	std::cout << "INFO LINK PROG LOG : " << infoLog << std::endl;
	glUseProgram(prog_id);
	

}

void	myopengl::shader::setModCamera()
{
	projMatrix = glm::perspective(45.0f, 800.0f / 600.0f,0.1f,100.0f);
	projMatrixLocation = glGetUniformLocation(prog_id,"projMatrix");
	 glUniformMatrix4fv(projMatrixLocation,1,GL_FALSE,&projMatrix[0][0]);


}

GLint	myopengl::shader::getProg()
{

	return prog_id;
}
