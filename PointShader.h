#pragma once
#include "ShaderProgram.h"
#include "glm.hpp"
#include "Definitions.h"

using glm::mat4x4;

class Particle;

class PointShader
{
public:
	PointShader(const mat4x4* const projectionMatrix, const bool useGeometryShader);
	~PointShader(void);
	
	void				useShader(const mat4x4* const viewMatrix, const ParticleStatus particleStatus, Particle* neighbours, const glm::vec2& windowSize);

private:
	ShaderProgram*		m_BasicShader;

	GLuint				m_ViewMatrixID;
	GLuint				m_ProjectionMatrixID;
	GLuint				m_ParticleStatus;
	GLuint				m_WindowSize;
	GLuint				m_NeighbourParticles;
	GLuint				m_CountNeighbourParticles;

	const mat4x4*		m_ProjectionMatrix;
};

