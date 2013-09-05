#include "create_vertex.h"

myopengl::vertexobj::vertexobj(myopengl::vertex*	vertices, GLubyte*	indices)
{
		glGenVertexArrays(1, &vaoid);
		glBindVertexArray(vaoid);
		glGenBuffers(1, &vboid);
		glBindBuffer(GL_ARRAY_BUFFER, vboid);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(myopengl::vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(myopengl::vertex), (GLvoid*)sizeof(vertices[0].xyzw));
		std::cout << vertices[0].xyzw << std::endl;
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glGenBuffers(1,&indexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

}

myopengl::vertexobj::~vertexobj()
{

}



void	myopengl::vertexobj::vertexDraw()
{
		glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,nullptr);
}
