#version 330 core
// Stencil Testing Fragment Shader

out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D screenTexture;

void main(){ 
	
	// Hardcoded outline color
	FragColor = vec4(0.04, 0.28, 0.26, 1.0);
}