#version 430

in vec2 vs_TexCoords;
out vec4 color;

uniform sampler2D samp;
uniform vec3 textColor;

void main()
{
	color = vec4(textColor.rgb, texture(samp, vs_TexCoords).r);
}