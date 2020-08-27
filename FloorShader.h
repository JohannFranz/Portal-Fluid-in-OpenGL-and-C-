#pragma once
#include "ShaderProgram.h"
#include "glm.hpp"

using glm::mat4x4;

class FloorShader
{
public:
	FloorShader(const mat4x4* const projectionMatrix);
	~FloorShader(void);

	void useShader(const mat4x4* const viewMatrix, const mat4x4* const modelMatrix);

private:
	ShaderProgram*		m_BasicShader;

	GLuint				m_MVP_MatrixID;

	const mat4x4*		m_ProjectionMatrix;
};

