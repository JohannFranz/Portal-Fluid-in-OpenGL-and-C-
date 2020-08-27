#pragma once

#include "glm.hpp"

using glm::mat4x4;
using glm::vec3;

class Math
{
public:
	static void		createRotationMatrix(	float angle, 
											const vec3& rotationAxis, 
											const vec3& normal, 
											mat4x4* rotMatrix
										);

	static void		randomSeed();
	static float	getRandomNumber(float lowerBoundary, float upperBoundary);

private:
	Math(void);
	~Math(void);
};
