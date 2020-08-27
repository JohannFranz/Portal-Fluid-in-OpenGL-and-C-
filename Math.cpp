#include "Math.h"
#include <ctime>

Math::Math(void)
{
}


Math::~Math(void)
{
}

//angle in radians
void Math::createRotationMatrix(float angle, const vec3& rotationAxis, const vec3& normal, mat4x4* rotMatrix)
{
	glm::mat3x3 rotCoord(	glm::normalize(rotationAxis), 
							glm::normalize(normal), 
							glm::normalize(glm::cross(rotationAxis, normal))
						);
	glm::mat3x3 invRotCoord = glm::transpose(rotCoord);
	glm::mat3x3 rotation(	vec3(1.0f, 0.0f, 0.0f), 
							vec3(0.0f, cos(angle), -sin(angle)), 
							vec3(0.0f, sin(angle), cos(angle))
						);
	rotation = rotCoord * rotation * invRotCoord;
	
	(*rotMatrix)[0][0] = rotation[0][0];
	(*rotMatrix)[0][1] = rotation[0][1];
	(*rotMatrix)[0][2] = rotation[0][2];
	(*rotMatrix)[0][3] = 0.0f;
	(*rotMatrix)[1][0] = rotation[1][0];
	(*rotMatrix)[1][1] = rotation[1][1];
	(*rotMatrix)[1][2] = rotation[1][2];
	(*rotMatrix)[1][3] = 0.0f;
	(*rotMatrix)[2][0] = rotation[2][0];
	(*rotMatrix)[2][1] = rotation[2][1];
	(*rotMatrix)[2][2] = rotation[2][2];
	(*rotMatrix)[2][3] = 0.0f;
	(*rotMatrix)[3][0] = 0.0f;
	(*rotMatrix)[3][1] = 0.0f;
	(*rotMatrix)[3][2] = 0.0f;
	(*rotMatrix)[3][3] = 1.0f;
}

void Math::randomSeed()
{
    srand(clock());
}

float Math::getRandomNumber(float lowerBoundary, float upperBoundary)
{
	if ( upperBoundary <= lowerBoundary )
		return 0.0f;

	int mod = abs(upperBoundary - lowerBoundary);
	float ret = rand() % mod + lowerBoundary;
	return ret;
}