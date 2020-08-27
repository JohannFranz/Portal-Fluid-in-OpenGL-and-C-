#version 430

layout(location=0) in vec3 vPosition;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform int particleState;


void main() {
	if ( particleState == 0 )
	{
		gl_Position = projectionMatrix * viewMatrix * vec4(vPosition, 1.0f);
	} else 
	{
		gl_Position = viewMatrix * vec4(vPosition, 1.0f);
	}
}