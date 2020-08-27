#include "Floor.h"
#include "FloorMesh.h"
#include "FloorShader.h"
#include <matrix_transform.inl>

Floor::Floor(const mat4x4* const projectionMatrix)
{
	m_FloorMesh = new FloorMesh(GL_STATIC_DRAW);
	m_FloorShader = new FloorShader(projectionMatrix);
	m_ModelMatrix = new mat4x4();

	//scale Floor
	float scaleFactor = 2;
	(*m_ModelMatrix) = glm::scale((*m_ModelMatrix), glm::vec3(scaleFactor, scaleFactor, scaleFactor));
}

Floor::~Floor(void)
{
}

void Floor::draw(const mat4x4* const viewMatrix)
{
	m_FloorShader->useShader(viewMatrix, m_ModelMatrix);
	m_FloorMesh->draw();
}

void Floor::update(const mat4x4* const transformation)
{
}