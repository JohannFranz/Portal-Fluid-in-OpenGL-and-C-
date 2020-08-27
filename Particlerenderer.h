#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>
#include "glm.hpp"
#include "Definitions.h"

class Particle;
class PointShader;

using glm::mat4x4;

class Particlerenderer
{
public:
	Particlerenderer(Particle* particles, const mat4x4* const projectionMatrix);
	~Particlerenderer(void);

	void			render(	const mat4x4* const viewMatrix, 
							const ParticleStatus particleStatus,
							const glm::vec2& windowSize);

private:
	void			loadBufferData();

	Particle*		m_ParticleBuffer;
	PointShader*	m_PointShaderG;
	PointShader*	m_PointShaderNG;

	GLuint			m_Vao;
	GLuint			m_VboParticlePos;
};

