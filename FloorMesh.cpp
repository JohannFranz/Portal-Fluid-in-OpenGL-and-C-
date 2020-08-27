#include "FloorMesh.h"


FloorMesh::FloorMesh(GLuint bufferType)
{
	GLfloat vertices[] = {	//erstes Dreieck
							-1.0f, 0.0f, 1.0f, 1.0f,  
							1.0f, 0.0f, 1.0f, 1.0f, 
							1.0f, 0.0f, -1.0f, 1.0f,
							//zweites Dreieck
							1.0f, 0.0f, -1.0f, 1.0f,
							-1.0f, 0.0f, -1.0f, 1.0f,
							-1.0f, 0.0f, 1.0f, 1.0f
	};
	
	GLfloat colors[] = {	//erstes Dreieck
							0.7f, 0.7f, 0.7f, 1.0f, 
							0.7f, 0.7f, 0.7f, 1.0f, 
							0.7f, 0.7f, 0.7f, 1.0f, 
							//zweites Dreieck
							0.8f, 0.8f, 0.8f, 1.0f, 
							0.7f, 0.7f, 0.7f, 1.0f, 
							0.7f, 0.7f, 0.7f, 1.0f
	};

	basicMesh = new Mesh(vertices, 6, 4, bufferType);
	basicMesh->setColors(colors, 4, bufferType);
}


FloorMesh::~FloorMesh(void)
{
}

void FloorMesh::draw()
{
	basicMesh->draw();
}