#version 430

//out vec4 out_Color;
in vec2 gs_TexCoord;

layout (location = 0) out vec4 accum;
layout (location = 1) out float reveal;

uniform sampler2D particleTexture;

void main()
{
	vec4 textured = texture(particleTexture, gs_TexCoord);
	//out_Color = textured;
	
	float weight = clamp(pow(min(1.0, textured.a * 10.0) + 0.01, 3.0) * 1e8 * pow(1.0 - gl_FragCoord.z * 0.9, 3.0), 1e-2, 3e3);

	accum = vec4(textured.rgb * textured.a, textured.a) * weight;

	reveal = textured.a;
}