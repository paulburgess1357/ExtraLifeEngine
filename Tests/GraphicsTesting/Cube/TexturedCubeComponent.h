#pragma once

struct TexturedCubeComponent {
	TexturedCubeComponent(const unsigned int vao)
		:m_vao{ vao } {
	}
	unsigned int m_vao;	
};
