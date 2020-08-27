#pragma once

#include "glm.hpp"

class TriangleMesh;
class TriangleShader;

class TriangleObject
{
public:
	TriangleObject(const glm::mat4x4* const projectionMatrix);
	~TriangleObject(void);

	void draw(const glm::mat4x4* const eyeMatrix);
	void update(const glm::mat4x4* const transformation);

private:
	
	TriangleMesh*		m_TriMesh;
	TriangleShader*		m_TriShader;
	glm::mat4x4*		m_ModelMatrix;
};

