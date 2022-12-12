#version 430

layout (location = 0) in vec3 in_Pos;

void main()
{
	gl_Position = vec4(in_Pos, 1.0f);
}