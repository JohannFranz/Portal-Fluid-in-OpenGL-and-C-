#include "Particleemitter.h"
#include <new>
#include "Math.h"
#include "Definitions.h"


Particleemitter::Particleemitter(vec3 startPosition, GLfloat startArea)
{
	m_StartPosition = startPosition;
	m_StartAreaLength = sqrt(startArea);

	Math::randomSeed();

	initParticleBuffer();
}

Particleemitter::~Particleemitter(void)
{
	for(int i = 0; i < NUM_OF_PARTICLES; ++i)
	{
		m_ParticleBuffer[i].~Particle();
	}
		
	free(m_ParticleBuffer);
}

void Particleemitter::initParticleBuffer()
{
	m_ParticleBuffer = new Particle[NUM_OF_PARTICLES];

	for(int i = 0; i < NUM_OF_PARTICLES; ++i)
	{
		m_ParticleBuffer[i].init(getNewParticlePosition(), getNewParticleVelocity());
	}
}

void Particleemitter::resetInactiveParticles()
{
	Particle* particles = m_ParticleBuffer;
	for( int i = 0; i < NUM_OF_PARTICLES; i++, particles++)
	{
		if (particles->isActive()) 
		{
			continue;	
		}

		particles->setVelocity(getNewParticleVelocity());
		particles->setPosition(getNewParticlePosition());
		particles->setActive(true);
	}
}

vec3 Particleemitter::getNewParticlePosition()
{
	vec3 position = m_StartPosition;
	position.z += Math::getRandomNumber(0, m_StartAreaLength*1000)*0.001f - (m_StartAreaLength * 0.5f);	
	position.y += Math::getRandomNumber(0, m_StartAreaLength*1000)*0.001f - (m_StartAreaLength * 0.5f);

	return position;
}

vec3 Particleemitter::getNewParticleVelocity()
{
	vec3 velocity;
	velocity.z = 0.0f;
	velocity.x -= Math::getRandomNumber(0, 3000)*0.001f;	
	velocity.y += Math::getRandomNumber(0, 2000)*0.001f;

	return velocity;
}

Particle* Particleemitter::getParticles()
{
	return m_ParticleBuffer;
}


