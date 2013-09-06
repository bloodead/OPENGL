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
			vertexobj(vertex*      vertices, GLubyte*        indices,size_t vertice_t, size_t indice_t);
			~vertexobj();
			void	vertexDraw();
			void	rotate(int	key);
	};



}




#endif
