#include "Particlerenderer.h"
#include "PointShader.h"
#include "Particle.h"

Particlerenderer::Particlerenderer(Particle* particles, const mat4x4* const projectionMatrix)
{
	m_ParticleBuffer = particles;

	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

	glGenBuffers(1, &m_VboParticlePos);
	loadBufferData();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);

	m_PointShaderG = new PointShader(projectionMatrix, true);
	m_PointShaderNG = new PointShader(projectionMatrix, false);
}

Particlerenderer::~Particlerenderer(void)
{
}

void Particlerenderer::loadBufferData()
{
	GLfloat positions[3*NUM_OF_PARTICLES];

	for ( int i = 0; i < NUM_OF_PARTICLES; i++ )
	{
		vec3 pos = m_ParticleBuffer[i].getPosition();
		for ( int j = 0; j < 3; j++ )
		{
			positions[i*3+j] = pos[j];
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VboParticlePos);
	glBufferData(GL_ARRAY_BUFFER, 3*NUM_OF_PARTICLES*sizeof(GLfloat), &positions, GL_DYNAMIC_DRAW);
}

void Particlerenderer::render(	const mat4x4* const viewMatrix, 
								const ParticleStatus particleStatus, 
								const glm::vec2& windowSize)
{
	glBindVertexArray(m_Vao);
	glEnableVertexAttribArray(0);
	glPointSize(3);
	loadBufferData();
	
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	if ( particleStatus == showParticle )
	{
		m_PointShaderNG->useShader(viewMatrix, particleStatus, m_ParticleBuffer, windowSize);
	} else
	{
		m_PointShaderG->useShader(viewMatrix, particleStatus, m_ParticleBuffer, windowSize);
	}
	glDrawArrays(GL_POINTS, 0, NUM_OF_PARTICLES);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}