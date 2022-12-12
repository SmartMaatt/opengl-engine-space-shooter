#version 430

layout (location = 0) in vec3 in_Position;
layout (location = 6) in vec3 in_Offset;

uniform mat4 lightSpaceMatrix;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = lightSpaceMatrix * modelMatrix * vec4(in_Position + in_Offset, 1.0);
}