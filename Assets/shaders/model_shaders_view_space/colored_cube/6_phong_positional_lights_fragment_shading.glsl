#version 330 core
// Fragment Shader
// Positional Lights
// OGL4 Shader Language Cookbook Pg. 112
// Pg. 86 for general light diagram

// Vertex Variables
in vec3 calculated_frag_color;

// Output
out vec4 fragment_color;

// Shader
void main() {	

	fragment_color = vec4(calculated_frag_color, 1.0);		
}
