#version 430 

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec3 v_normal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;
layout(location = 5) in vec2 v_textcoord;
layout(location = 6) in vec3 offset;

void main() {
  gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(v_position + offset, 1.0f);

  vec4 worldPos = ModelMatrix * vec4(v_position + offset, 1.0f);
  FragPos = worldPos.xyz;
  TexCoords = v_textcoord;
  mat3 normalMatrix = transpose(inverse(mat3(ModelMatrix)));
  Normal = normalMatrix * v_normal;

  gl_Position = ProjectionMatrix * ViewMatrix * worldPos;
}