#include "TriangleMesh.h"


TriangleMesh::TriangleMesh(GLuint bufferType)
{
	GLfloat vertices[] = {	//erstes Dreieck
							-0.5f, -0.5f, 0.5f, 1.0f,  
							0.5f, -0.5f, 0.5f, 1.0f, 
							0.0f, 0.5f, 0.5f, 1.0f,
							//zweites Dreieck
							0.5f, -0.5f, 0.5f, 1.0f, 
							0.0f, 0.5f, 0.5f, 1.0f,
							0.0f, 0.0f, -0.5f, 1.0f,
							//drittes Dreieck
							-0.5f, -0.5f, 0.5f, 1.0f,  
							0.0f, 0.5f, 0.5f, 1.0f,
							0.0f, 0.0f, -0.5f, 1.0f,
							//viertes Dreieck
							-0.5f, -0.5f, 0.5f, 1.0f,  
							0.5f, -0.5f, 0.5f, 1.0f, 
							0.0f, 0.0f, -0.5f, 1.0f,
	};
	
	GLfloat colors[] = {	//erstes Dreieck
							1.0f, 1.0f, 0.0f, 1.0f, 
							1.0f, 0.0f, 1.0f, 1.0f, 
							0.0f, 1.0f, 1.0f, 1.0f,
							//zweites Dreieck
							1.0f, 1.0f, 0.0f, 1.0f, 
							1.0f, 0.0f, 1.0f, 1.0f, 
							0.0f, 1.0f, 1.0f, 1.0f,
							//drittes Dreieck
							1.0f, 1.0f, 0.0f, 1.0f, 
							1.0f, 0.0f, 1.0f, 1.0f, 
							0.0f, 1.0f, 1.0f, 1.0f, 
							//viertes Dreieck
							1.0f, 1.0f, 0.0f, 1.0f, 
							1.0f, 0.0f, 1.0f, 1.0f, 
							0.0f, 1.0f, 1.0f, 1.0f
	};

	basicMesh = new Mesh(vertices, 12, 4, bufferType);
	basicMesh->setColors(colors, 4, bufferType);
}


TriangleMesh::~TriangleMesh(void)
{
}

void TriangleMesh::draw()
{
	basicMesh->draw();
}