#version 430 

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

out vec3 v_Color;
out vec2 v_TextCoord;
out vec3 v_Normal;
out vec3 v_Position;

out mat3 TBN;

out vec3 v_Offset;

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec3 v_normal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;
layout(location = 5) in vec2 v_textcoord;
layout(location = 6) in vec3 offset;

void main() {
	vec3 T = normalize(vec3(ModelMatrix * vec4(aTangent, 0.0)));
	vec3 N = normalize(vec3(ModelMatrix * vec4(v_normal + offset, 0.0)));
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);

	TBN = mat3(T, B, N);

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(v_position + offset, 1.0f);

	v_Color = v_color;
	v_TextCoord = v_textcoord;  
	v_Normal = mat3(transpose(inverse(ModelMatrix))) * normalize((v_normal + offset));
	v_Position =  vec3(ModelMatrix * vec4(v_position + offset, 1.0));

	v_Offset = offset;
}