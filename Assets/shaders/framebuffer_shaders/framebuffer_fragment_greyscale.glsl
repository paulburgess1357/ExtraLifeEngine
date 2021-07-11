#version 330 core
// Framebuffer Fragment Shader

out vec4 fragment_color;
in vec2 fragment_tex_coords;
uniform sampler2D screen_quad;

void main(){ 
	// Framebuffer Greyscale
     fragment_color = texture(screen_quad, fragment_tex_coords);
     float average = 0.2126 * fragment_color.r + 0.7152 * fragment_color.g + 0.0722 * fragment_color.b;
     fragment_color = vec4(average, average, average, 1.0);	
}