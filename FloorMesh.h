#pragma once
#include "Mesh.h"

class FloorMesh
{
public:
	FloorMesh(GLuint bufferType);
	~FloorMesh(void);

	void draw();

private:
	Mesh* basicMesh;

};

