#pragma once
#include "glm.hpp"

using glm::mat4x4;

class FloorMesh;
class FloorShader;

class Floor
{
public:
	Floor(const mat4x4* const projectionMatrix);
	~Floor(void);

	void draw(const mat4x4* const viewMatrix);
	void update(const mat4x4* const transformation);

private:
	
	FloorMesh*		m_FloorMesh;
	FloorShader*	m_FloorShader;
	mat4x4*			m_ModelMatrix;
};

