#version 430

layout (location = 0) out vec4 frag;

layout (binding = 0) uniform sampler2D accumulative;
layout (binding = 1) uniform sampler2D revealage;

const float EPSILON = 0.00001f;

bool isEqual(float a, float b)
{
	return abs(a - b) <= (abs(a) < abs(b) ? abs(b) : abs(a)) * EPSILON;
}

float maxOfVec3(vec3 v)
{
	return max(max(v.x, v.y), v.z);
}

void main()
{
	ivec2 coords = ivec2(gl_FragCoord.xy);

	float revealage = texelFetch(revealage, coords, 0).r;

	if(isEqual(revealage, 1.0f))
		discard;

	vec4 accumulation = texelFetch(accumulative, coords, 0);

	if(isinf(maxOfVec3(abs(accumulation.rgb))))
		accumulation.rgb = vec3(accumulation.a);

	vec3 avgColor = accumulation.rgb / max(accumulation.a, EPSILON);

	frag = vec4(avgColor, 1.0f - revealage);
}