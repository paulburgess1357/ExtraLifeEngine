#pragma once

struct CubeMapComponent {
	CubeMapComponent(const unsigned int vao)
		:m_vao{ vao } {
	}
	unsigned int m_vao;
};
