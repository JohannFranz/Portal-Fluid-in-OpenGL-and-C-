#pragma once

#include "glm.hpp"
#include "Definitions.h"

using glm::vec3;
using glm::mat4x4;

class Particleemitter;
class Particlerenderer;

class ParticleManager
{
public:
	ParticleManager(const mat4x4* const projectionMatrix);
	~ParticleManager(void);

	void update(double time);
	void render(const mat4x4* const viewMatrix, const ParticleStatus particleStatus, const glm::vec2& windowSize);

private:
	Particleemitter*	m_Emitter;
	Particlerenderer*	m_Renderer;
};

