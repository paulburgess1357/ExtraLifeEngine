#pragma once

struct VertexAndNormals {

	VertexAndNormals() = default;

	VertexAndNormals(const unsigned char x, const unsigned char y, 
		const unsigned char z, const unsigned char w, const unsigned char n1, 
		const unsigned char n2, const unsigned char n3)
		:m_x{ x },
		m_y{ y },
		m_z{ z },
		m_w{ w },
		m_n1{ n1 },
		m_n2{ n2 },
		m_n3{ n3 }{
	}

	// position
	unsigned char m_x = 0;
	unsigned char m_y = 0;
	unsigned char m_z = 0;

	// type
	unsigned char m_w = 0;

	// normals
	unsigned char m_n1 = 0;
	unsigned char m_n2 = 0;
	unsigned char m_n3 = 0;
};
