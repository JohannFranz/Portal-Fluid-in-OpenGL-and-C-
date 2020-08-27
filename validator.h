#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string>


class Validator {

public:
	static void checkShaderCompileStatus( GLuint shaderID, std::string shaderName );
	static void checkShaderLinkStatus( GLuint shaderID );
	static void checkShaderValidationStatus( GLuint shaderID );

private:
	Validator(void);
	~Validator(void);


};