#include "OpenGLChunk.h"
#include "../../ResourceManagement/GraphicsConstants.h"
#include <glad/glad.h>

OpenGL::OpenGLChunk::OpenGLChunk(const WorldPosition& starting_world_position, const unsigned int vbo, const unsigned int vao)
	:Chunk(starting_world_position),
	m_vbo{ vbo },
	m_vao{ vao }{
}

OpenGL::OpenGLChunk::~OpenGLChunk() {
	if(m_vbo != GraphicsConstants::UNINITIALIZED_VALUE && m_vao != GraphicsConstants::UNINITIALIZED_VALUE){
		// Print::print("Destroying Chunk Data");
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

void OpenGL::OpenGLChunk::set_vbo(const unsigned int vbo) {
	m_vbo = vbo;
}

void OpenGL::OpenGLChunk::set_vao(const unsigned int vao) {
	m_vao = vao;
}

bool OpenGL::OpenGLChunk::vbo_vao_initialized() const{
	if(m_vbo == GraphicsConstants::UNINITIALIZED_VALUE || m_vao == GraphicsConstants::UNINITIALIZED_VALUE){
		return false;
	}
	return true;
}

void OpenGL::OpenGLChunk::destroy() const{
	if (m_vbo != GraphicsConstants::UNINITIALIZED_VALUE && m_vao != GraphicsConstants::UNINITIALIZED_VALUE) {
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
	}
}
