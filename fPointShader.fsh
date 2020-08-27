#version 430

out vec4 fColor;
in vec3 particlePosition;

uniform mat4 viewMatrix;
uniform int particleState;
uniform vec2 windowSize;
uniform vec3 neighbourParticles[20];
uniform int countNeighbourParticles;

float maxDistanceRadialBasisFunction = 0.5f;
float isoValue = 0.2f;
float isoError = 0.00001f;
float expValue = -7.0f;

float gradientStep = 0.000001f;
int   raySteps = 100;


float getRadialBasisValue(vec3 position)
{
	float val = 0.0f;
	float distance = 0.0f;
	for (int i = 0; i < countNeighbourParticles; i++) {
		vec4 neighbour = viewMatrix * vec4(neighbourParticles[i], 1.0f);
		distance = length(position - neighbour.xyz);

		if ( particleState == 2 ) {
			if ( distance < maxDistanceRadialBasisFunction ) {
				val += maxDistanceRadialBasisFunction - distance;
			} 
		} else if ( particleState == 3 ){
			val += exp(expValue * distance);
		}
	}
	
	return val;
}

vec3 getGradient(vec3 position)
{
	vec3 gradient;

	for (int i = 0; i < 3; i++) {
		vec3 diffStepPlus = position;
		vec3 diffStepMinus = position;
		diffStepPlus[i] += gradientStep;
		diffStepMinus[i] -= gradientStep;
		gradient[i] = getRadialBasisValue(diffStepPlus) - getRadialBasisValue(diffStepMinus);
	}

	return -normalize(gradient);
}

vec4 getShadingColor(vec3 position, vec3 normal)
{
	//define light sources
	vec3 lightPos = vec3(2.0f,2.0f,2.0f);
	vec3 diffuseColor = vec3(1.0f, 0.0f, 0.0f);

	vec3 specularColor = vec3(1.0f, 1.0f, 1.0f);
	float specular = 0.0f;
	float specularIntensity = 0.5f;
	float diffuseIntensity = 0.9f;

	vec3 lightDir = normalize(lightPos - position);
	float dotNV = dot(normal, -normalize(position));
	float dotNL = dot(normal, lightDir);

	//calc diffuse color
	float lambertian = diffuseIntensity * max(dotNL, 0.0f);
	diffuseColor *= lambertian;

	//calc specular color
	if(lambertian > 0.0f) {
		vec3 reflectDir = normalize(2*dotNL*normal-lightDir);

		float specAngle = max(dot(reflectDir, -normalize(position)), 0.0f);
		//specular = specularIntensity * pow(specAngle, 100.0f);
		float F = 0.2f * pow((1.0-dotNV), 2);
		specular = specularIntensity * F / dotNV;
	}

	return vec4(diffuseColor + specular*specularColor, 1.0f);
}

vec4 getSurfaceColor()
{
	//Raycast-Schnittpunkt bestimmen
	float rayCastInterval = length(particlePosition) * (1.0f / raySteps);
	vec3 interval = normalize(particlePosition) * rayCastInterval;
	vec3 position = vec3(0.0f, 0.0f, 0.0f);
	float radBasVal;
	float count = 0;

	for (int i = 0; i < raySteps; i++)
	{
		position += interval;
		radBasVal = getRadialBasisValue(position);
		
		if (radBasVal < isoValue) continue;
		
		float error = 1.0f;
		while (error > isoError && count < 50)
		{
			interval *= 0.5f;

			if (radBasVal < isoValue) 
			{
				position += interval;
			} else 
			{ 
				position -= interval;
			}

			radBasVal = getRadialBasisValue(position);
			error = abs(isoValue - radBasVal);
			count++;
		}

		vec3 normal = getGradient(position);
		return getShadingColor(position, normal);
	}
	if (count == 0) discard;
	
	return vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

void main() {
	if ( particleState == 0 ){
		fColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	} else if ( particleState == 1 ){
		float halfWidth = windowSize.x*0.5f;
		float halfHeight = windowSize.y*0.5f;

		float x = (gl_FragCoord.x - halfWidth) / halfWidth;
		float y = (gl_FragCoord.y - halfHeight) / halfHeight;

		fColor = vec4(x, y, 0.0f, 1.0f); 
	} else if ( particleState > 1 ) {
		fColor = getSurfaceColor();
	} 
}