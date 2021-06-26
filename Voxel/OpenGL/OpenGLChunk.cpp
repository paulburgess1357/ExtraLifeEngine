#include "OpenGLChunk.h"
#include "../../ResourceManagement/OpenGL/OpenGLConstants.h"
#include "../../Utility/Print.h"
#include <glad/glad.h>

OpenGL::OpenGLChunk::OpenGLChunk(const WorldPosition& starting_world_position, const unsigned int vbo, const unsigned int vao)
	:Chunk(starting_world_position),
	m_vbo{ vbo },
	m_vao{ vao }{
}

OpenGL::OpenGLChunk::~OpenGLChunk() {
	if(m_vbo != OpenGL::UNINITIALIZED_CHUNK_VALUE && m_vao != OpenGL::UNINITIALIZED_CHUNK_VALUE){
		Print::print("Destroying Chunk Data");
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
	}
}

unsigned int OpenGL::OpenGLChunk::get_vao() const{
	return m_vao;
}

unsigned OpenGL::OpenGLChunk::get_vbo() const{
	return m_vbo;
}

void OpenGL::OpenGLChunk::destroy() const{
	if (m_vbo != OpenGL::UNINITIALIZED_CHUNK_VALUE && m_vao != OpenGL::UNINITIALIZED_CHUNK_VALUE) {
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
	}
}


