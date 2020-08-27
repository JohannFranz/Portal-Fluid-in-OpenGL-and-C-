#version 430

layout(location=0) in vec4 vPosition;
layout(location=1) in vec4 vColor;

uniform mat4 mvpMatrix;

out vec4 color;

void main() {
	color = vColor;
	gl_Position = mvpMatrix * vPosition;
}