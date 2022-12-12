#version 430

layout (location = 0) in vec4 in_Pos_TextCoords;
out vec2 vs_TexCoords;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(in_Pos_TextCoords.xy, 0.0, 1.0);
	vs_TexCoords = vec2(in_Pos_TextCoords.zw);
}