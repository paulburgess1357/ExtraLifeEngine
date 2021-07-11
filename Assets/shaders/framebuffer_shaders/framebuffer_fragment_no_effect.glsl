#version 330 core
// Framebuffer Fragment Shader

out vec4 fragment_color;
in vec2 fragment_tex_coords;
uniform sampler2D screen_quad;

void main(){ 
	// No Framebuffer Effect
	fragment_color = texture(screen_quad, fragment_tex_coords);
}