#include "OpenGLChunk.h"
#include "../../Utility/Print.h"
#include <glad/glad.h>

unsigned int OpenGL::OpenGLChunk::m_uninitialized_chunk_value = 999999;

OpenGL::OpenGLChunk::OpenGLChunk(const WorldPosition& starting_world_position)
	:Chunk(starting_world_position),
	m_vbo{ m_uninitialized_chunk_value },
	m_vao{ m_uninitialized_chunk_value }{
	initialize_vbo_vao();
}

OpenGL::OpenGLChunk::~OpenGLChunk() {
	if(m_vbo != m_uninitialized_chunk_value && m_vao != m_uninitialized_chunk_value){
		Print::print("Destroying Chunk Data");
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
	}
}

void OpenGL::OpenGLChunk::initialize_vbo_vao() {
	if(m_vbo == m_uninitialized_chunk_value && m_vao == m_uninitialized_chunk_value){
		glGenBuffers(1, &m_vbo);
		glGenVertexArrays(1, &m_vao);
	}
}

unsigned int OpenGL::OpenGLChunk::get_vao() const{
	return m_vao;
}

unsigned OpenGL::OpenGLChunk::get_vbo() const{
	return m_vbo;
}

void OpenGL::OpenGLChunk::destroy() const{
	if (m_vbo != m_uninitialized_chunk_value && m_vao != m_uninitialized_chunk_value) {
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
	}
}


