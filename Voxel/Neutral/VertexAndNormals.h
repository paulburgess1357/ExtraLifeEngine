#pragma once

struct VertexAndNormals {

	VertexAndNormals() = default;

	VertexAndNormals(const signed char x, const signed char y, 
		const signed char z, const signed char w, const signed char n1, 
		const signed char n2, const signed char n3)
		:m_x{ x },
		m_y{ y },
		m_z{ z },
		m_w{ w },
		m_n1{ n1 },
		m_n2{ n2 },
		m_n3{ n3 }{
	}

	// position
	signed char m_x = 0;
	signed char m_y = 0;
	signed char m_z = 0;

	// type
	signed char m_w = 0;

	// normals
	signed char m_n1 = 0;
	signed char m_n2 = 0;
	signed char m_n3 = 0;
};