#include "OpenGLChunk.h"
#include "../Neutral/VertexAndNormals.h"
#include "../../Utility/Print.h"
#include <glad/glad.h>

// TODO Optimization
// Move the chunk vector loading into Chunk (and rename this to possilbly chunk)
// When the chunk is initiated, get and store the adjacent chunks.  That way
// when checking faces on adjacent chunks, the pointers are already created and I
// don't have to do the lookup again (e.g. does it exist, etc.).  Its done right
// when the chunk is created.

OpenGL::OpenGLChunk::OpenGLChunk(const WorldPosition& starting_world_position,
                                 const std::shared_ptr<IShaderProgram>& shader_program,
                                 const std::shared_ptr<ChunkManager>& chunk_manager)
	:Chunk(starting_world_position, shader_program, chunk_manager),
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

void OpenGL::OpenGLChunk::render() const {

	// Skip drawing empty chunks
	if (m_vertex_qty == 0) {
		return;
	}

	m_shader_program->set_uniform("model_matrix", m_model_matrix);
	m_shader_program->set_uniform("normal_matrix", m_normal_matrix);
	m_shader_program->bind();

	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vertex_qty);
	glBindVertexArray(0);

	m_shader_program->unbind();
}

void OpenGL::OpenGLChunk::update() {

	if (!m_update_required) {
		return;
	}

	//Print::print("Loading Chunk Data...");
	m_update_required = false;

	std::vector<VertexAndNormals> chunk_data = load_chunk_data();

	// TODO keep an eye on this for future bugs/crashes...
	// When a chunk is completely surrounded, it may not have any data at all to send to the gpu.  This causes
	// a crash when doing vertex[0] (below), as there is nothing in the vector that you are accessing.
	if(m_vertex_qty == 0){
		return;
	}

	// Bind Buffers
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// Store Data
	glBufferData(GL_ARRAY_BUFFER, chunk_data.size() * sizeof(VertexAndNormals), &chunk_data.front(), GL_STATIC_DRAW);

	// Vertex Data
	glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, 7 * sizeof(signed char), (void*)0);
	glEnableVertexAttribArray(0);

	// Normals
	glVertexAttribPointer(1, 3, GL_BYTE, GL_FALSE, 7 * sizeof(signed char), (void*)(4 * sizeof(signed char)));
	glEnableVertexAttribArray(1);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

