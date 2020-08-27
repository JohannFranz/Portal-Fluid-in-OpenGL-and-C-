#pragma once
#include "ShaderProgram.h"
#include "glm.hpp"

class TriangleShader
{
public:
	TriangleShader(const glm::mat4x4* const projectionMatrix);
	~TriangleShader(void);

	void useShader(const glm::mat4x4* const viewMatrix, const glm::mat4x4* const modelMatrix);

private:
	ShaderProgram*		m_BasicShader;

	GLuint				m_MVP_MatrixID;

	const glm::mat4x4*	m_ProjectionMatrix;
};

