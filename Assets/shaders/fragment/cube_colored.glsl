#version 330 core

out vec4 fragment_color;
uniform vec3 cube_color;

void main() {
    fragment_color = vec4(cube_color, 1.0); // set all 4 vector values to 1.0
}