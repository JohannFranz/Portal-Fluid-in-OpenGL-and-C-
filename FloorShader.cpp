#include "FloorShader.h"


FloorShader::FloorShader(const mat4x4* const projectionMatrix)
	: m_ProjectionMatrix(projectionMatrix)
{
	string shaderFiles[] = {	"vFloorShader.vsh",
								"fFloorShader.fsh"
							};
	m_BasicShader = new ShaderProgram( 2, shaderFiles );

	m_MVP_MatrixID = glGetUniformLocation(m_BasicShader->getProgramID(),"mvpMatrix");
}

FloorShader::~FloorShader(void)
{
}

void FloorShader::useShader (const mat4x4* const viewMatrix, const mat4x4* const modelMatrix)
{
	mat4x4 mvpMatrix = (*m_ProjectionMatrix) * (*viewMatrix) * (*modelMatrix);
	glUseProgram(m_BasicShader->getProgramID());
	glUniformMatrix4fv(m_MVP_MatrixID, 1, GL_FALSE, (GLfloat*) &mvpMatrix);
}