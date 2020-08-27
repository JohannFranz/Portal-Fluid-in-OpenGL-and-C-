#version 430

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 projectionMatrix;

out vec3 particlePosition;

float billBoardLength = 0.5f;

void main() {
	int x,y;
	vec4 pos;
	
	for (x = -1; x < 2; x+=2)
	{
		for (y = -1; y < 2; y+=2)
		{
			pos = gl_in[0].gl_Position;
			
			pos.x += x*billBoardLength;
			pos.y += y*billBoardLength;
			//pos.z += billBoardLength;
			particlePosition = pos.xyz;

			gl_Position = projectionMatrix * pos;
			EmitVertex();
		}
	}
	EndPrimitive();
}