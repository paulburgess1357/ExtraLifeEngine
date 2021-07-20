#version 330 core
// Fragment Shader
// Discard Fragments
// Using 2 sided shading
// OGL4 Shader Language Cookbook Pg. 107

// Note an alternative method for 2 sided shading is to use the gl_FrontFacing
// variable (pg96)

// Vertex Variables
in vec3 calculated_frag_color;
in vec2 frag_texture_coords;

// Output
out vec4 fragment_color;

// Shader
void main() {	

	const float scale = 15.0f;
	bvec2 to_discard = greaterThan(fract(frag_texture_coords * scale), vec2(0.2f, 0.2f));

	if(all(to_discard)){
		discard;
	}

	fragment_color = vec4(calculated_frag_color, 1.0);		
}
