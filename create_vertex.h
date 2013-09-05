#ifndef _CREATE_VERTEX_H_
#define	_CREATE_VERTEX_H_
#include <iostream>
#include <string> 
#include <GL/glew.h>


namespace myopengl
{
	struct	vertex
	{
		GLfloat	xyzw[4];
		GLfloat	rgba[4];
	};

	class	vertexobj
	{
		private:
			GLuint	vaoid;
			GLuint	vboid;
			GLuint	indexBufferId;
		public:
			vertexobj(myopengl::vertex*        vertices, GLubyte*        indices);
			~vertexobj();
			void	vertexDraw();
	};



}




#endif
