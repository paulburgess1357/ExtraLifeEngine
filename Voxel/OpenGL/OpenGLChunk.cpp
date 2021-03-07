#include "OpenGLChunk.h"
#include "../Neutral/VertexAndNormals.h"
#include "../../Utility/Print.h"
#include <glad/glad.h>

OpenGL::OpenGLChunk::OpenGLChunk(const WorldPosition& starting_world_position,
                                 const std::shared_ptr<IShaderProgram>& shader_program)
	:Chunk(starting_world_position, shader_program),
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

//void OpenGL::OpenGLChunk::render() const {
//
//	// Skip drawing empty chunks
//	if (m_vertex_qty == 0) {
//		return;
//	}
//
//	m_shader_program->set_uniform("model_matrix", m_model_matrix);
//	m_shader_program->set_uniform("normal_matrix", m_normal_matrix);
//	m_shader_program->bind();
//
//	glBindVertexArray(m_vao);
//	glDrawArrays(GL_TRIANGLES, 0, m_vertex_qty);
//	glBindVertexArray(0);
//
//	m_shader_program->unbind();
//}

void OpenGL::OpenGLChunk::update() {

	if (!m_update_required) {
		return;
	}
	
	m_update_required = false;
	std::vector<VertexAndNormals> chunk_data = load_chunk_data();

	if(m_vertex_qty == 0){
		return;
	}

	// Bind Buffers
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// Store Data
	glBufferData(GL_ARRAY_BUFFER, chunk_data.size() * sizeof(VertexAndNormals), &chunk_data.front(), GL_STATIC_DRAW);

	// Vertex Data
	glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, 7 * sizeof(unsigned char), (void*)0);
	glEnableVertexAttribArray(0);

	// Normals
	glVertexAttribPointer(1, 3, GL_BYTE, GL_FALSE, 7 * sizeof(unsigned char), (void*)(4 * sizeof(unsigned char)));
	glEnableVertexAttribArray(1);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

