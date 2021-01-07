#version 330 core

// Vertex Variables
in vec3 fragment_world_position;
in vec4 texcoord;

// Output
out vec4 fragment_color;


// Shader
void main() {        

    //fragment_color = vec4(texcoord.w / 128.0, texcoord.w / 256.0, texcoord.w / 512.0, 1.0);
    fragment_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}