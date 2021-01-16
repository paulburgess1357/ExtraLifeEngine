#include "OpenGLChunk.h"
#include "../Neutral/VertexAndNormals.h"
#include "../../Utility/Print.h"
#include <glad/glad.h>

#include "../../Utility/FatalError.h"

OpenGL::OpenGLChunk::OpenGLChunk(const WorldPosition& starting_world_position,
                                 const std::shared_ptr<IShaderProgram>& shader_program,
                                 const std::shared_ptr<ChunkManager>& chunk_manager)
	:IChunk(starting_world_position, shader_program),
	m_vbo{ 99 },
	m_vao{ 99 },
	m_chunkmanager{ chunk_manager }{
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

	// When creating chunks larger than 15x15x15 a vector is required.
	// It is possible to create this vertex using:
	// VertexAndNormals vertex[CX * CY * CZ * 6 * 6];  However, this is
	// created on the stack and you will quickly run into memory issues when
	// creating chunks larger than 15x15x15.

	//Print::print("Current chunk world position: " + std::to_string(m_world_position.x) + "," + std::to_string(m_world_position.y) + "," + std::to_string(m_world_position.z));

	//if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::LEFT)) {
	//	Print::print("Chunk Exists to the LEFT!");
	//}

	//if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::RIGHT)) {
	//	Print::print("Chunk Exists to the RIGHT!");
	//}

	//if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::TOP)) {
	//	Print::print("Chunk Exists ABOVE!");
	//}

	//if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::BOTTOM)) {
	//	Print::print("Chunk Exists BELOW!");
	//}

	//if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::FRONT)) {
	//	Print::print("Chunk Exists to the FRONT!");
	//}

	//if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::BACK)) {
	//	Print::print("Chunk Exists to the BACK!");
	//}



	std::vector<VertexAndNormals> vertex;
	for (signed char x = 0; x < CX; x++) {
		for (signed char y = 0; y < CY; y++) {
			for (signed char z = 0; z < CZ; z++) {
				const signed char type = m_block_types[x][y][z];

				// Skip Empty Blocks
				if (type == 0) {
					continue;
				}

				//TODO I can probably change this: if (x > 0 && m_block_types[x - 1][y][z] == 0)
				//TODO to this: m_block_types[x - 1][y][z] == 0

				// left face (negative x)		
				if (x == 0) {
					if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::LEFT)) {

						// If drawing left edge of current chunk and there exists a chunk to our left:
						// Get adjacent chunk:
						const std::shared_ptr<IChunk> adjacent_chunk = m_chunkmanager->get_adjacent_chunk(m_world_position, AdjacentChunkPosition::LEFT);

						// Check edge of adjacent chunk (right edge)
						// If the adjacent chunk right edge is not being drawn, draw left edge of current chunk
						if (adjacent_chunk->get(CX - 1, y, z) == 0) {
							emplace_left_face(vertex, x, y, z, type);
						}
					} else {

						// If drawing left edge and there is no chunk to our left, draw left edge of current chunk						
						emplace_left_face(vertex, x, y, z, type);
					}
				} else {

					// Since we aren't on the outer left edge of our chunk, we only need to compare
					// within the current chunk
					if (m_block_types[x - 1][y][z] == 0) {

						// If the block within our current chunk to our left is not being drawn,
						// draw left edge of current block
						emplace_left_face(vertex, x, y, z, type);
					}
				}


				// right face (positive x)
				if (x == CX - 1) {
					if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::RIGHT)) {

						// If drawing right edge and a chunk exists to our right:
						// Get adjacent chunk:
						const std::shared_ptr<IChunk> adjacent_chunk = m_chunkmanager->get_adjacent_chunk(m_world_position, AdjacentChunkPosition::RIGHT);

						// Check edge of adjacent chunk (left edge)
						// If the adjacent chunk left edge is not being drawn, draw right edge of current chunk:
						if (adjacent_chunk->get(0, y, z) == 0) {
							emplace_right_face(vertex, x, y, z, type);
						}

					} else {

						// If drawing right edge and no chunk exists to our right, draw right edge of current chunk
						emplace_right_face(vertex, x, y, z, type);
					}

				} else {

					// Since we aren't on the right edge of our chunk, we only need to compare
					// with the current chunk:

					// If the block within our current chunk to our right is not being drawn,
					// draw right edge of current chunk
					if (m_block_types[x + 1][y][z] == 0) {
						emplace_right_face(vertex, x, y, z, type);
					}


				}


				// front face (positive z)
				//if ((z > 0 && m_block_types[x][y][z - 1] == 0) || (z == 0)) {
				//
				//

				// front face (positive z)

				if (z == CZ - 1) {

					if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::FRONT)) {
						const std::shared_ptr<IChunk> adjacent_chunk = m_chunkmanager->get_adjacent_chunk(m_world_position, AdjacentChunkPosition::FRONT);

						if (adjacent_chunk == nullptr) {
							FatalError::fatal_error("This shouldn't be a nullptr!!");
						}

						if (adjacent_chunk->get(x, y, 0) == 0) {
							emplace_front_face(vertex, x, y, z, type);
						}

					} else {
						emplace_front_face(vertex, x, y, z, type);
					}


				} else {
					if (m_block_types[x][y][z + 1] == 0) {
						emplace_front_face(vertex, x, y, z, type);
					}
				}
















				// back face (negative z)

				if (z == 0) {

					if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::BACK)) {
						const std::shared_ptr<IChunk> adjacent_chunk = m_chunkmanager->get_adjacent_chunk(m_world_position, AdjacentChunkPosition::BACK);
						if (adjacent_chunk == nullptr) {
							FatalError::fatal_error("This shouldn't be a nullptr!!");
						}

						if (adjacent_chunk->get(x, y, CZ - 1) == 0) {
							emplace_back_face(vertex, x, y, z, type);
						}

					} else {
						emplace_back_face(vertex, x, y, z, type);
					}


				} else {
					if (m_block_types[x][y][z - 1] == 0) {
						emplace_back_face(vertex, x, y, z, type);
					}
				}




				// top face (positive y)
				if (y == CY - 1) {
					if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::TOP)) {
						const std::shared_ptr<IChunk> adjacent_chunk = m_chunkmanager->get_adjacent_chunk(m_world_position, AdjacentChunkPosition::TOP);
						if (adjacent_chunk->get(x, 0, z) == 0) {
							emplace_top_face(vertex, x, y, z, type);
						}
					} else {
						emplace_top_face(vertex, x, y, z, type);
					}
				} else {
					if (m_block_types[x][y + 1][z] == 0) {
						emplace_top_face(vertex, x, y, z, type);
					}
				}

				// bottom face (negative y)
				if (y == 0) {
					if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::BOTTOM)) {

						// If drawing bottom edge of current chunk and there exists a chunk below:

						// Get adjacent chunk
						const std::shared_ptr<IChunk> adjacent_chunk = m_chunkmanager->get_adjacent_chunk(m_world_position, AdjacentChunkPosition::BOTTOM);

						// Check edge of the adjacent chunk (top edge)
						// If the adjacent chunk top edge is not being drawn, draw the bottom edge of the current chunk:
						if (adjacent_chunk->get(x, CY - 1, z) == 0) {
							emplace_bottom_face(vertex, x, y, z, type);
						}

					} else {

						// If drawing bottom edge and there is no chunk below, draw current chunk:
						emplace_bottom_face(vertex, x, y, z, type);

					}



				} else {

					// Since we aren't on the outer bottom edge of our chunk, we only need to compare
					// with the current chunk
					if (m_block_types[x][y - 1][z] == 0) {
						emplace_bottom_face(vertex, x, y, z, type);
					}
				}
			}
		}
	}

	m_vertex_qty = static_cast<int>(vertex.size());

	// TODO keep an eye on this for future bugs/crashes...
	// When a chunk is completely surrounded, it may not have any data at all to send to the gpu.  This causes
	// a crash when doing vertex[0] (below), as there is nothing in the vector that you are accessing.
	if(m_vertex_qty == 0){
		return;
	}
	//what is faster/better? &vertex.front() will work and not crash.  However, its probalby faster to still do the return and
	//exit early since we don't need to send anything to the gpu.

	

	// Bind Buffers
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// Store Data
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(VertexAndNormals), &vertex.front(), GL_STATIC_DRAW);

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

