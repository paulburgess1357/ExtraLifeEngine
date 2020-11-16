#version 330 core
// Textured cube shader (no lighting)
// Note: For multiple textures, you may need to enable: 
// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)

in vec2 tex_coords;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 fragment_color;

void main() {
    fragment_color = mix(texture(texture1, tex_coords), texture(texture2, tex_coords), 0.4);
}