#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string>

using std::string;

class ShaderProgram
{
public:
	ShaderProgram(GLsizei numShaderParts, string* shaderFiles);
	~ShaderProgram(void);

	GLuint getProgramID();

private:
	void makeVertexShader(string sourceCode);
	void makeFragmentShader(string sourceCode);
	void makeGeometryShader(string sourceCode);
	void makeShaderProgram();
	

	GLuint m_ShaderProgramID;
	GLuint m_VertexShaderID;
	GLuint m_FragmentShaderID;
	GLuint m_GeometryShaderID;
};

