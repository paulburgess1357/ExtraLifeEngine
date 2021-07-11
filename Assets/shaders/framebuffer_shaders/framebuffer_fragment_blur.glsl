#version 330 core
// Framebuffer Fragment Shader

out vec4 fragment_color;
in vec2 fragment_tex_coords;
uniform sampler2D screen_quad;

void main(){ 

	// Framebuffer Blur
    float offset = 1.0 / 300.0; 
	vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    // Blur Kernel
    float kernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16  
    );

    vec3 sample_tex[9];
    for(int i = 0; i < 9; i++){
        sample_tex[i] = vec3(texture(screen_quad, fragment_tex_coords.st + offsets[i]));
    }
    
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++){
        col += sample_tex[i] * kernel[i];
    }        
    
    fragment_color = vec4(col, 1.0);
}
