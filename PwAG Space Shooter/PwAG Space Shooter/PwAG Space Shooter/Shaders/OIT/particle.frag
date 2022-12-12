#version 430

//out vec4 out_Color;
in vec2 gs_TexCoord;

layout (location = 0) out vec4 accumulative;
layout (location = 1) out float revealage;

uniform sampler2D particleTexture;

void main()
{
	vec4 textured = texture(particleTexture, gs_TexCoord);
	//out_Color = textured;
	
	float weightValue = clamp(pow(min(1.0, textured.a * 10.0) + 0.01, 3.0) * 1e8 * pow(1.0 - gl_FragCoord.z * 0.9, 3.0), 1e-2, 3e3);

	accumulative = vec4(textured.rgb * textured.a, textured.a) * weightValue;

	revealage = textured.a;
}