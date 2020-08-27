#pragma once
#include "Particle.h"
#include <GL\glew.h>
#include <GL\freeglut.h>

class Particleemitter
{
public:
	Particleemitter(vec3 startPosition, GLfloat startArea = 0.0f);
	~Particleemitter(void);

	Particle*		getParticles();

	void			resetInactiveParticles();

private:
	void			initParticleBuffer();

	vec3			getNewParticlePosition();
	vec3			getNewParticleVelocity();

	Particle*		m_ParticleBuffer;

	vec3			m_StartPosition;
	GLfloat			m_StartAreaLength;
};

