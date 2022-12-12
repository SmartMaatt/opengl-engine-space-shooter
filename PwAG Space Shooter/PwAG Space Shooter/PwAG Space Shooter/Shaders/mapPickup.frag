#version 430 

layout (location = 0) out vec4 accum;
layout (location = 1) out float reveal;

uniform sampler2D diffuse;

uniform vec3 cameraPos;

in vec3 v_Color;
in vec2 v_TextCoord;
in vec3 v_Normal;
in vec3 v_Position;

struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define MAX_POINT_LIGHT_COUNT 64

uniform PointLight pointLights[MAX_POINT_LIGHT_COUNT];
uniform int pointLightsCount;

void main()
{
	if (gl_FrontFacing) {
		vec3 result = vec3(0.0, 0.0, 0.0);
		for(int i = 0; i < pointLightsCount; ++i)
		{
			vec3 textured = texture(diffuse, v_TextCoord).rgb;

			// ambient light
			vec3 ambientFinal = vec3(1.0,1.0,1.0) * textured;
	
			// attentuation
			float distance = length(pointLights[i].position - v_Position);
			// constant linear quadric
			float attentuation = 1.0 / (pointLights[i].constant + pointLights[i].linear * distance + pointLights[i].quadratic * (distance * distance));

			ambientFinal *= attentuation;
			result += ambientFinal;
		}	
		vec4 color = vec4(result, 1.0);

		float weight = clamp(pow(min(1.0, color.a * 10.0) + 0.01, 3.0) * 1e8 * pow(1.0 - gl_FragCoord.z * 0.9, 3.0), 1e-2, 3e3);

		accum = vec4(color.rgb * color.a, color.a) * weight;

		reveal = color.a;
	}
}