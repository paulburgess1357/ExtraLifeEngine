#version 330 core
// Framebuffer Fragment Shader

out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D screenTexture;

void main(){ 
	// No Framebuffer Effect
	FragColor = texture(screenTexture, TexCoords);
}