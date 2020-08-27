#include "TriangleShader.h"


TriangleShader::TriangleShader(const glm::mat4x4* const projectionMatrix)
	: m_ProjectionMatrix(projectionMatrix)
{
	string shaderFiles[] = {	"vertexShader.vsh",
								"fragmentShader.fsh"
							};
	m_BasicShader = new ShaderProgram( 2, shaderFiles );

	m_MVP_MatrixID = glGetUniformLocation(m_BasicShader->getProgramID(),"mvpMatrix");
}

TriangleShader::~TriangleShader(void)
{
}

void TriangleShader::useShader (const glm::mat4x4* const viewMatrix, const glm::mat4x4* const modelMatrix)
{
	glm::mat4x4 invViewMatrix = glm::inverse((*viewMatrix));
	glm::mat4x4 mvpMatrix = (*m_ProjectionMatrix) * invViewMatrix * (*modelMatrix);
	glUseProgram(m_BasicShader->getProgramID());
	glUniformMatrix4fv(m_MVP_MatrixID, 1, GL_FALSE, (GLfloat*) &mvpMatrix);

}