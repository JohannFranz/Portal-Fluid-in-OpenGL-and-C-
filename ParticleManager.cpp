#include "ParticleManager.h"
#include "Particleemitter.h"
#include "Particlerenderer.h"
#include "vec2.hpp"

ParticleManager::ParticleManager(const mat4x4* const projectionMatrix)
{
	m_Emitter = new Particleemitter(vec3(1.5f, 2.5f, 0.0f), 1);
	m_Renderer = new Particlerenderer(m_Emitter->getParticles(), projectionMatrix);
}

ParticleManager::~ParticleManager(void)
{
}

void ParticleManager::update(double time)
{
	Particle* particles = m_Emitter->getParticles();

	for( int i = 0; i < NUM_OF_PARTICLES; i++)
	{
		particles->update(time);
		particles++;
	}

	m_Emitter->resetInactiveParticles();
}

void ParticleManager::render(const mat4x4* const viewMatrix, const ParticleStatus particleStatus, const glm::vec2& windowSize)
{
	m_Renderer->render(viewMatrix, particleStatus, windowSize);
}