#version 430

in vec2 vs_TextCoords;

layout (location = 0) out vec4 frag;

uniform sampler2D samp;

void main()
{
	frag = vec4(texture(samp, vs_TextCoords).rgb, 1.0f);
}