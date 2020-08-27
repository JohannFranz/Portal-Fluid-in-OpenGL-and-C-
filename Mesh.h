#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>

class Mesh
{
public:
	Mesh(GLfloat* vertices, GLuint numVertices, GLuint numValuesPerVertex, GLuint bufferType);
	~Mesh(void);

	void setColors(GLfloat* colors, GLuint numValuesPerVertex, GLuint bufferType);
	void setIndices(GLfloat* indices, GLuint numIndices, GLuint bufferType);

	void draw();

private:
	
	GLuint m_Vao;
	GLuint m_VboPositions;
	GLuint m_VboColors;
	GLuint m_VboIndex;
	GLuint m_VboTextureCoords;	//todo: für zukünftige Anwendungen interessant
	GLuint m_VboNormals;		//todo: für zukünftige Anwendungen interessant
	GLuint m_VboTangent;		//todo: für zukünftige Anwendungen interessant
	GLuint m_NumVertices;		
};

