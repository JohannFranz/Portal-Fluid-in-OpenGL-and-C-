#include "Mesh.h"


Mesh::Mesh(GLfloat* vertices, GLuint numVertices, GLuint numValuesPerVertex, GLuint bufferType)
	:m_VboColors(0), m_VboTextureCoords(0), m_VboNormals(0), m_VboTangent(0), m_NumVertices(numVertices)
{
	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

	glGenBuffers(1, &m_VboPositions);
	glBindBuffer(GL_ARRAY_BUFFER, m_VboPositions);
	glBufferData(GL_ARRAY_BUFFER, numValuesPerVertex*m_NumVertices*sizeof(GLfloat), vertices, bufferType);
	glVertexAttribPointer(0, numValuesPerVertex, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh(void)
{
}

void Mesh::setColors(GLfloat* colors, GLuint numValuesPerColor, GLuint bufferType)
{
	glBindVertexArray(m_Vao);
	glGenBuffers(1, &m_VboColors);
	glBindBuffer(GL_ARRAY_BUFFER, m_VboColors);
	glBufferData(GL_ARRAY_BUFFER, numValuesPerColor*m_NumVertices* sizeof(GLfloat), colors, bufferType);
	glVertexAttribPointer(1, numValuesPerColor, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
}

	//GLuint indices[] = {0,1,2,3};
void Mesh::setIndices(GLfloat* indices, GLuint numIndices, GLuint bufferType)
{
	glBindVertexArray(m_Vao);
	glGenBuffers(1, &m_VboIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VboIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices*sizeof(GLuint), indices, bufferType);
	glBindVertexArray(0);
}

void Mesh::draw()
{
	glBindVertexArray(m_Vao);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(0);
	
	glDrawArrays(GL_TRIANGLES, 0, m_NumVertices);
	//glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, NULL);

	
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}