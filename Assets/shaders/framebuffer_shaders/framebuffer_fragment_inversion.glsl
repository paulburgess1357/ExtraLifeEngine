#version 330 core
// Framebuffer Fragment Shader

out vec4 fragment_color;
in vec2 fragment_tex_coords;
uniform sampler2D screen_quad;

void main(){ 	
	// Framebuffer Inversion:
	fragment_color = vec4(vec3(1.0 - texture(screen_quad, fragment_tex_coords)), 1.0);	
}
