#pragma once
#include <cstdint>
#include <glad/glad.h>
#include "glm/glm.hpp"

#define CX 16
#define CY 16
#define CZ 16

//GLbyte is int8?
typedef glm::tvec4<GLbyte> byte4;

//TODO vao instead of vbo?
//TODO store block data on heap? yes most likley necessary
//TODO check vbo call with existing cube stuff
//TODO add vao

namespace OpenGL{
	
	class OpenGLChunk {

	public:
		OpenGLChunk();
		~OpenGLChunk();

		uint8_t get(const int x, const int y, const int z) const;
		void set(const int x, const int y, const int z, uint8_t type);
		void update();
		void render();

	private:
		uint8_t m_block_types[CX][CY][CZ];
		unsigned int m_vbo;
		int m_block_qty;
		bool m_contents_changed;

	};
	
} //namespace OpenGL



