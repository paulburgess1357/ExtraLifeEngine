#version 330 core
// Textured cube shader (no lighting)

in vec2 tex_coords;

uniform sampler2D texture1;

out vec4 fragment_color;

void main() {
    fragment_color = texture(texture1, tex_coords);
}