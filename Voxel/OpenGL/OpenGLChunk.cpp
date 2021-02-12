#include "OpenGLChunk.h"
#include "../Neutral/VertexAndNormals.h"
#include "../Neutral/GreedyMesh.h"
#include "../Neutral/GreedyFacePerRowMesh.h"
#include "../Neutral/GreedyRowPerSideMesh.h"
#include "../../Utility/Print.h"
#include <glad/glad.h>
#include <algorithm>

// TODO Optimization
// Move the chunk vector loading into IChunk (and rename this to possilbly chunk)
// When the chunk is initiated, get and store the adjacent chunks.  That way
// when checking faces on adjacent chunks, the pointers are already created and I
// don't have to do the lookup again (e.g. does it exist, etc.).  Its done right
// when the chunk is created.

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


	// Testing for greedy meshing:
	std::vector<VertexAndNormals> left_vertex;
	std::vector<VertexAndNormals> right_vertex;
	std::vector<VertexAndNormals> top_vertex;
	std::vector<VertexAndNormals> bottom_vertex;
	std::vector<VertexAndNormals> front_vertex;
	std::vector<VertexAndNormals> back_vertex;	
		
	for (signed char x = 0; x < CX; x++) {
		for (signed char y = 0; y < CY; y++) {			
			for (signed char z = 0; z < CZ; z++) {
				const signed char type = m_block_types[x][y][z];
				
				//Print::print(std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z));
				
				// Skip Empty Blocks (Removed during the greedy mesh step)
				if (type == 0) {			
					continue;
				}

				// left face (negative x)		
				if (x == 0) {
					if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::LEFT)) {

						// If drawing left edge of current chunk and there exists a chunk to our left:
						// Get adjacent chunk:
						const std::shared_ptr<IChunk> adjacent_chunk = m_chunkmanager->get_adjacent_chunk(m_world_position, AdjacentChunkPosition::LEFT);

						// Check edge of adjacent chunk (right edge)
						// If the adjacent chunk right edge is not being drawn, draw left edge of current chunk
						if (adjacent_chunk->get(CX - 1, y, z) == 0) {
							emplace_left_face(left_vertex, x, y, z, type);
						}
					} else {

						// If drawing left edge and there is no chunk to our left, draw left edge of current chunk						
						emplace_left_face(left_vertex, x, y, z, type);
					}
				} else {

					// Since we aren't on the outer left edge of our chunk, we only need to compare
					// within the current chunk
					if (m_block_types[x - 1][y][z] == 0) {

						// If the block within our current chunk to our left is not being drawn,
						// draw left edge of current block
						emplace_left_face(left_vertex, x, y, z, type);
					}
				}
				
				// right face (positive x)
				if (x == CX - 1) {
					if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::RIGHT)) {
						const std::shared_ptr<IChunk> adjacent_chunk = m_chunkmanager->get_adjacent_chunk(m_world_position, AdjacentChunkPosition::RIGHT);
						if (adjacent_chunk->get(0, y, z) == 0) {
							emplace_right_face(right_vertex, x, y, z, type);
						}
					} else {
						emplace_right_face(right_vertex, x, y, z, type);
					}
				} else {
					if (m_block_types[x + 1][y][z] == 0) {
						emplace_right_face(right_vertex, x, y, z, type);
					}
				}

				// front face (positive z)
				if (z == CZ - 1) {
					if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::FRONT)) {
						const std::shared_ptr<IChunk> adjacent_chunk = m_chunkmanager->get_adjacent_chunk(m_world_position, AdjacentChunkPosition::FRONT);
						if (adjacent_chunk->get(x, y, 0) == 0) {
							emplace_front_face(front_vertex, x, y, z, type);
						}
					} else {
						emplace_front_face(front_vertex, x, y, z, type);
					}
				} else {
					if (m_block_types[x][y][z + 1] == 0) {
						emplace_front_face(front_vertex, x, y, z, type);
					}
				}

				// back face (negative z)
				if (z == 0) {
					if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::BACK)) {						
						const std::shared_ptr<IChunk> adjacent_chunk = m_chunkmanager->get_adjacent_chunk(m_world_position, AdjacentChunkPosition::BACK);
						if (adjacent_chunk->get(x, y, CZ - 1) == 0) {
							emplace_back_face(back_vertex, x, y, z, type);
						}
					} else {
						emplace_back_face(back_vertex, x, y, z, type);
					}
				} else {
					if (m_block_types[x][y][z - 1] == 0) {
						emplace_back_face(back_vertex, x, y, z, type);
					}
				}

				// top face (positive y)
				if (y == CY - 1) {
					if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::TOP)) {						
						const std::shared_ptr<IChunk> adjacent_chunk = m_chunkmanager->get_adjacent_chunk(m_world_position, AdjacentChunkPosition::TOP);
						if (adjacent_chunk->get(x, 0, z) == 0) {
							emplace_top_face(top_vertex, x, y, z, type);
						}
					} else {
						emplace_top_face(top_vertex, x, y, z, type);
					}
				} else {
					if (m_block_types[x][y + 1][z] == 0) {
						emplace_top_face(top_vertex, x, y, z, type);
					}
				}

				// bottom face (negative y)
				if (y == 0) {
					if (m_chunkmanager->adjacent_chunk_exists(m_world_position, AdjacentChunkPosition::BOTTOM)) {
						const std::shared_ptr<IChunk> adjacent_chunk = m_chunkmanager->get_adjacent_chunk(m_world_position, AdjacentChunkPosition::BOTTOM);
						if (adjacent_chunk->get(x, CY - 1, z) == 0) {
							emplace_bottom_face(bottom_vertex, x, y, z, type);
						}
					} else {
						emplace_bottom_face(bottom_vertex, x, y, z, type);
					}
				} else {

					// Since we aren't on the outer bottom edge of our chunk, we only need to compare
					// with the current chunk
					if (m_block_types[x][y - 1][z] == 0) {
						emplace_bottom_face(bottom_vertex, x, y, z, type);
					}
				}
				
			}			
		}
	}

	// TODO Greedy meshing here?
	std::vector<VertexAndNormals> row_merged_left_vertex = GreedyFacePerRowMesh::merge_all_faces(left_vertex, FaceType::LEFT);
	std::vector<VertexAndNormals> final_merged_left_vertex = GreedyRowPerSideMesh::merge_rows(row_merged_left_vertex, FaceType::LEFT);		
	std::vector<VertexAndNormals> new_left_vertex = final_merged_left_vertex;
	
	std::vector<VertexAndNormals> row_merged_right_vertex = GreedyFacePerRowMesh::merge_all_faces(right_vertex, FaceType::RIGHT);
	std::vector<VertexAndNormals> final_merged_right_vertex = GreedyRowPerSideMesh::merge_rows(row_merged_right_vertex, FaceType::RIGHT);	
	std::vector<VertexAndNormals> new_right_vertex = final_merged_right_vertex;
			

	std::vector<Face> front_face_vector = GreedyMesh::convert_vertex_vector_to_face_vector(front_vertex);
	std::sort(front_face_vector.begin(), front_face_vector.end(), less_than_front_faces());
	std::vector<VertexAndNormals> front_face_vector_after_sort = GreedyMesh::convert_faces_vertor_to_vertexnormals(front_face_vector);
	std::vector<VertexAndNormals> row_merged_front_vertex = GreedyFacePerRowMesh::merge_all_faces(front_face_vector_after_sort, FaceType::FRONT);
	std::vector<VertexAndNormals> final_merged_front_vertex = GreedyRowPerSideMesh::merge_rows(row_merged_front_vertex, FaceType::FRONT);
	std::vector<VertexAndNormals> new_front_vertex = final_merged_front_vertex;

	
	std::vector<Face> back_face_vector = GreedyMesh::convert_vertex_vector_to_face_vector(back_vertex);
	std::sort(back_face_vector.begin(), back_face_vector.end(), less_than_front_faces());
	std::vector<VertexAndNormals> back_face_vector_after_sort = GreedyMesh::convert_faces_vertor_to_vertexnormals(back_face_vector);
	std::vector<VertexAndNormals> row_merged_back_vertex = GreedyFacePerRowMesh::merge_all_faces(back_face_vector_after_sort, FaceType::BACK);
	std::vector<VertexAndNormals> final_merged_back_vertex = GreedyRowPerSideMesh::merge_rows(row_merged_back_vertex, FaceType::BACK);
	std::vector<VertexAndNormals> new_back_vertex = final_merged_back_vertex;

	std::vector<Face> top_face_vector = GreedyMesh::convert_vertex_vector_to_face_vector(top_vertex);
	std::sort(top_face_vector.begin(), top_face_vector.end(), less_than_top_bottom_faces());
	std::vector<VertexAndNormals> top_face_vector_after_sort = GreedyMesh::convert_faces_vertor_to_vertexnormals(top_face_vector);	
	std::vector<VertexAndNormals> row_merged_top_vertex = GreedyFacePerRowMesh::merge_all_faces(top_face_vector_after_sort, FaceType::TOP);	
	std::vector<VertexAndNormals> final_merged_top_vertex = GreedyRowPerSideMesh::merge_rows(row_merged_top_vertex, FaceType::TOP);
	std::vector<VertexAndNormals> new_top_vertex = final_merged_top_vertex;
	
	// Combine into one vertex
	std::vector<VertexAndNormals> vertex;
	vertex.reserve(new_left_vertex.size() + new_right_vertex.size() + new_front_vertex.size() + new_back_vertex.size() + new_top_vertex.size() + bottom_vertex.size());
	vertex.insert(vertex.end(), new_left_vertex.begin(), new_left_vertex.end());
	vertex.insert(vertex.end(), new_right_vertex.begin(), new_right_vertex.end());
	vertex.insert(vertex.end(), new_front_vertex.begin(), new_front_vertex.end());
	vertex.insert(vertex.end(), new_back_vertex.begin(), new_back_vertex.end());
	vertex.insert(vertex.end(), new_top_vertex.begin(), new_top_vertex.end());
	vertex.insert(vertex.end(), bottom_vertex.begin(), bottom_vertex.end());
	

	m_vertex_qty = static_cast<int>(vertex.size());

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

