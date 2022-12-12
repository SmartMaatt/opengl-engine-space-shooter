#version 430 

out vec2 v_TextCoord;

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 v_textcoord;

void main() {
	v_TextCoord = v_textcoord;  
	gl_Position = vec4(v_position, 1.0f);
}