#include "ShaderProgram.h"
#include "validator.h"
#include "IOManager.h"

/*Shader werden in folgender Reihenfolge erzeugt:
	1. VertexShader
	2. FragmentShader
	3. GeometryShader, falls numShaderParts größer als 2 ist */
ShaderProgram::ShaderProgram(GLsizei numShaderParts, std::string* shaderFiles)
	: m_GeometryShaderID(0)
{
	makeVertexShader(shaderFiles[0]);
	makeFragmentShader(shaderFiles[1]);
	if (numShaderParts == 3) {
		makeGeometryShader(shaderFiles[2]);
	}
	makeShaderProgram();
}


ShaderProgram::~ShaderProgram(void)
{
	glDeleteProgram(m_ShaderProgramID);
}

void ShaderProgram::makeVertexShader(string sourceCode)
{
	const char* vertexShaderSourceCode = IOManager::readFile(sourceCode.c_str());
	m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(m_VertexShaderID, 1, (const GLchar**)&vertexShaderSourceCode, NULL);
	glCompileShader(m_VertexShaderID);

	Validator::checkShaderCompileStatus(m_VertexShaderID, "Vertex Shader");
}

void ShaderProgram::makeFragmentShader(string sourceCode)
{
	const char* fragmentShaderSourceCode = IOManager::readFile(sourceCode.c_str());
	m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_FragmentShaderID, 1, (const GLchar**)&fragmentShaderSourceCode, NULL);
	glCompileShader(m_FragmentShaderID);

	Validator::checkShaderCompileStatus(m_FragmentShaderID, "Fragment Shader");
}

void ShaderProgram::makeGeometryShader(string sourceCode)
{
	const char* geometryShaderSourceCode = IOManager::readFile(sourceCode.c_str());
	m_GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

	glShaderSource(m_GeometryShaderID, 1, (const GLchar**)&geometryShaderSourceCode, NULL);
	glCompileShader(m_GeometryShaderID);

	Validator::checkShaderCompileStatus(m_GeometryShaderID, "Geometry Shader");
}

void ShaderProgram::makeShaderProgram()
{
	m_ShaderProgramID = glCreateProgram();
	glAttachShader(m_ShaderProgramID, m_VertexShaderID);
	glAttachShader(m_ShaderProgramID, m_FragmentShaderID);
	if (m_GeometryShaderID != 0) {
		glAttachShader(m_ShaderProgramID, m_GeometryShaderID);
	}

	glLinkProgram(m_ShaderProgramID);
	Validator::checkShaderLinkStatus(m_ShaderProgramID);

	glValidateProgram(m_ShaderProgramID);
	Validator::checkShaderValidationStatus(m_ShaderProgramID);
}

GLuint ShaderProgram::getProgramID()
{
	return m_ShaderProgramID;
}