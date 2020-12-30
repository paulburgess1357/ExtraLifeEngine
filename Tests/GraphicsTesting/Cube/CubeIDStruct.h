#pragma once

struct CubeIDStruct{

	CubeIDStruct() = default;
	
	CubeIDStruct(unsigned int vbo_id, unsigned int vao_id, unsigned int ebo_id)
		:m_vbo_id{ vbo_id },
		 m_vao_id{ vao_id },
		 m_ebo_id{ ebo_id }{		
	}

	unsigned int m_vbo_id { 99 };
	unsigned int m_vao_id { 99 };
	unsigned int m_ebo_id { 99 };
	
};