#include "PointShader.h"
#include "Particle.h"

PointShader::PointShader(const mat4x4* const projectionMatrix, const bool useGeometryShader)
	: m_ProjectionMatrix(projectionMatrix)
{
	if ( useGeometryShader )
	{
		string shaderFiles[] = {	"vPointShader.vsh",
									"fPointShader.fsh",
									"gPointShader.gsh"
							};
		m_BasicShader = new ShaderProgram( 3, shaderFiles );
	} else
	{
		string shaderFiles[] = {	"vPointShader.vsh",
									"fPointShader.fsh"
							};
		m_BasicShader = new ShaderProgram( 2, shaderFiles );
	}
	
	GLuint programID = m_BasicShader->getProgramID();

	m_ViewMatrixID = glGetUniformLocation(programID,"viewMatrix");
	m_ProjectionMatrixID = glGetUniformLocation(programID,"projectionMatrix");
	m_ParticleStatus = glGetUniformLocation(programID,"particleState");
	m_WindowSize = glGetUniformLocation(programID,"windowSize");
	m_NeighbourParticles = glGetUniformLocation(programID,"neighbourParticles");
	m_CountNeighbourParticles = glGetUniformLocation(programID,"countNeighbourParticles");
}

PointShader::~PointShader(void)
{
}

void PointShader::useShader (const mat4x4* const viewMatrix, const ParticleStatus particleStatus, Particle* neighbours, const glm::vec2& windowSize)
{
	vec3 particles[NUM_OF_PARTICLES];
	int countActiveParticles = 0;
	for( int i = 0; i < NUM_OF_PARTICLES; i++ ){
		if (neighbours[i].isActive() == false) continue;

		countActiveParticles++;
		particles[i] = neighbours[i].getPosition();
	}

	glUseProgram(m_BasicShader->getProgramID());
	glUniformMatrix4fv(m_ViewMatrixID, 1, GL_FALSE, (GLfloat*)viewMatrix);
	glUniformMatrix4fv(m_ProjectionMatrixID, 1, GL_FALSE, (GLfloat*)m_ProjectionMatrix);

	glUniform3fv(m_NeighbourParticles, NUM_OF_PARTICLES, (GLfloat*)particles);
	glUniform1i(m_CountNeighbourParticles, countActiveParticles);

	glUniform1i(m_ParticleStatus, particleStatus);
	glUniform2f(m_WindowSize, (GLfloat)windowSize.x, (GLfloat)windowSize.y);
}