#version 430

layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec2 in_TextCoords;

out vec2 vs_TextCoords;

void main()
{
	vs_TextCoords = in_TextCoords;
	gl_Position = vec4(in_Pos, 1.0f);
}