#version 330 core
// Fragment Shader
// Phong Lighting 2 Sided
// OGL4 Shader Language Cookbook Pg. 98

// Note an alternative method for 2 sided shading is to use the gl_FrontFacing
// variable (pg96)

// Vertex Variables
in vec3 calculated_frag_color;

// Output
out vec4 fragment_color;

// Shader
void main() {	
	fragment_color = vec4(calculated_frag_color, 1.0);		

	// Somewhat related to 2 sided shading, but has nothing to do with the
	// method in the vertex shader. We can check back faces and winding order
	// by simply tweaking the fragment shader output by mixing in a color with
	// either the front face or backface.  This allows us to check a models
	// winding order (e.g. for when a model doesn't use the correct winding
	// order).  Note that winding order does not affect our lighting in this
	// shader example.  See page 98 (this uses the gl_FrontFacing method).

}
