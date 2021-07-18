#version 330 core
// Framebuffer Fragment Shader

out vec4 fragment_color;
in vec2 fragment_tex_coords;
uniform sampler2D screen_quad;

void main(){ 
	// Gamma Correction
	float gamma = 2.2;
	fragment_color.rgb = pow(texture(screen_quad, fragment_tex_coords).rgb, vec3(1.0/gamma));
}