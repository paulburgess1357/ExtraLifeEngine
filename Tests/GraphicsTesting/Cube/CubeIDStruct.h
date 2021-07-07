#pragma once
#include "../../../ResourceManagement/GraphicsConstants.h"

struct CubeIDStruct{
	CubeIDStruct() = default;	
	CubeIDStruct(const unsigned int vbo_id, const unsigned int vao_id, const unsigned int ebo_id)
		:m_vbo_id{ vbo_id },
		 m_vao_id{ vao_id },
		 m_ebo_id{ ebo_id }{		
	}

	unsigned int m_vbo_id { GraphicsConstants::UNINITIALIZED_VALUE };
	unsigned int m_vao_id { GraphicsConstants::UNINITIALIZED_VALUE };
	unsigned int m_ebo_id { GraphicsConstants::UNINITIALIZED_VALUE };
};
