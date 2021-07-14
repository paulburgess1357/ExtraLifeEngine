#version 330 core
// Framebuffer Fragment Shader

out vec4 fragment_color;
in vec2 fragment_tex_coords;
uniform sampler2D screen_quad;

void main(){ 
	// HDR Framebuffer Effect
	vec3 hdr_color = texture(screen_quad, fragment_tex_coords).rgb;
	fragment_color = vec4(hdr_color, 1);
}