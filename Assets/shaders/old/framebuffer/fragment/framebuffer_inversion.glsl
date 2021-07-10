#version 330 core
// Framebuffer Fragment Shader

out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D screenTexture;

void main(){ 	
	// Framebuffer Inversion:
	FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);	
}
