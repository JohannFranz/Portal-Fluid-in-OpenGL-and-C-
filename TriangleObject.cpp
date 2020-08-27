#include "TriangleObject.h"
#include "TriangleMesh.h"
#include "triangleshader.h"

TriangleObject::TriangleObject(const glm::mat4x4* const projectionMatrix)
{
	m_TriMesh = new TriangleMesh(GL_STATIC_DRAW);
	m_TriShader = new TriangleShader(projectionMatrix);
	m_ModelMatrix = new glm::mat4x4();
}

TriangleObject::~TriangleObject(void)
{
}

void TriangleObject::draw(const glm::mat4x4* const eyeMatrix)
{
	m_TriShader->useShader(eyeMatrix, m_ModelMatrix);
	m_TriMesh->draw();
}

void TriangleObject::update(const glm::mat4x4* const transformation)
{
	//(*m_ModelMatrix) = (*transformation)*(*m_ModelMatrix);
}