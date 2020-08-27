
#include "validator.h"
#include <iostream>

void Validator::checkShaderCompileStatus( GLuint shaderID, std::string shaderName )
{
	GLint param;
	glGetShaderiv( shaderID, GL_COMPILE_STATUS, &param);
	if ( param == 0 ) {
		GLsizei* length = new GLsizei;
		GLchar* infoLog = new GLchar[1024];
		glGetShaderInfoLog(shaderID, 1024, length, infoLog);
		std::string output = shaderName + ": %s\n";
		printf(output.c_str(),infoLog);
	}
}

void Validator::checkShaderLinkStatus( GLuint shaderID )
{
	GLint param;
	glGetProgramiv(shaderID, GL_LINK_STATUS, &param);
	if ( param == 0 ) {
		GLsizei* length = new GLsizei;
		GLchar* infoLog = new GLchar[1024];
		glGetShaderInfoLog(shaderID, 1024, length, infoLog);
		printf("Link status: %s\n",infoLog);
	}
}

void Validator::checkShaderValidationStatus( GLuint shaderID )
{
	GLint param;
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &param);
	if ( param == 0 ) {
		GLsizei* length = new GLsizei;
		GLchar* infoLog = new GLchar[1024];
		glGetShaderInfoLog(shaderID, 1024, length, infoLog);
		printf("Validate status: %s\n",infoLog);
	}
}