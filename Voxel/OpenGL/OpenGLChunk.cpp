#include "OpenGLChunk.h"
#include "../../Utility/Print.h"
#include <glad/glad.h>

OpenGL::OpenGLChunk::OpenGLChunk(const WorldPosition& starting_world_position)
	:Chunk(starting_world_position),
	m_vbo{ 99 },
	m_vao{ 99 }{
	initialize_vbo_vao();
}

OpenGL::OpenGLChunk::~OpenGLChunk() {
	Print::print("Destroying Chunk Data");
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void OpenGL::OpenGLChunk::initialize_vbo_vao() {
	Print::print("Initializing Chunk VBO and VAO");
	glGenBuffers(1, &m_vbo);
	glGenVertexArrays(1, &m_vao);
}

unsigned int OpenGL::OpenGLChunk::get_vao() const{
	return m_vao;
}

unsigned OpenGL::OpenGLChunk::get_vbo() const{
	return m_vbo;
}

