#pragma once
#include "Mesh.h"

class TriangleMesh
{
public:
	TriangleMesh(GLuint bufferType);
	~TriangleMesh(void);

	void draw();

private:
	Mesh* basicMesh;

};

