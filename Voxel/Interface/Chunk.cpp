#include "Chunk.h"
#include "../GreedyMesh/GreedyMeshExecutor.h"
#include "../../Utility/Print.h"
#include "../../Matrix/MatrixFunctions.h"
#include <glm/gtc/matrix_transform.hpp>

Chunk::Chunk(const WorldPosition& starting_world_position,
	const std::shared_ptr<IShaderProgram>& shader_program)
	:m_block_types{},
	m_vertex_qty{ 0 },
	m_update_required{ true },
	m_model_matrix{ glm::translate(glm::mat4(1), starting_world_position.get_vec3()) },
	m_normal_matrix{ MatrixFunctions::get_normal_matrix(m_model_matrix) },
	m_world_position{ starting_world_position },
	m_shader_program{ shader_program }{
	initialize_types();	
}

Chunk::~Chunk() = default;

signed char Chunk::get(const signed char x, const signed char y, const signed char z) const {
	return m_block_types[x][y][z];
}

void Chunk::set(const signed char x, const signed char y, const signed char z, const signed char type) {
	m_block_types[x][y][z] = type;
	m_update_required = true;
}

void Chunk::initialize_types() {
	for (signed char x = 0; x < CX; x++) {
		for (signed char y = 0; y < CY; y++) {
			for (signed char z = 0; z < CZ; z++) {
				int RANDOMVALUE = rand() % 4;
				//if(RANDOMVALUE == 0 || RANDOMVALUE == 1 || RANDOMVALUE == 2){
				//	RANDOMVALUE = 0;
				//}
				m_block_types[x][y][z] = RANDOMVALUE;
			}
		}
	}
}

std::vector<VertexAndNormals> Chunk::load_chunk_data() {

	// When creating chunks larger than 15x15x15 a vector is required.
	// It is possible to create this vertex using:
	// VertexAndNormals vertex[CX * CY * CZ * 6 * 6];  However, this is
	// created on the stack and you will quickly run into memory issues when
	// creating chunks larger than 15x15x15.

	// Split voxels into separate faces for greedy meshing:
	std::vector<VertexAndNormals> left_faces;
	std::vector<VertexAndNormals> right_faces;
	std::vector<VertexAndNormals> top_faces;
	std::vector<VertexAndNormals> bottom_faces;
	std::vector<VertexAndNormals> front_faces;
	std::vector<VertexAndNormals> back_faces;

	for (signed char x = 0; x < CX; x++) {
		for (signed char y = 0; y < CY; y++) {
			for (signed char z = 0; z < CZ; z++) {
				const signed char type = m_block_types[x][y][z];

				// Skip Empty Blocks
				if (type == 0) {
					continue;
				}
				std::shared_ptr<Chunk> test = nullptr;
				// Left face (negative x)				
				if (x == 0) {
					if (m_left_chunk != nullptr) {

						// If drawing left edge of current chunk and there exists a chunk to our left:
						// Check edge of adjacent chunk (right edge)
						// If the adjacent chunk right edge is not being drawn, draw left edge of current chunk
						
						if (m_left_chunk->get(CX - 1, y, z) == 0) {
							emplace_left_face(left_faces, x, y, z, type);
						}
					} else {
						
						// If drawing left edge and there is no chunk to our left, draw left edge of current chunk						
						emplace_left_face(left_faces, x, y, z, type);
					}
				} else {

					// Since we aren't on the outer left edge of our chunk, we only need to compare
					// within the current chunk (The adjacent chunk as not impact)
					
					if (m_block_types[x - 1][y][z] == 0) {

						// If the block within our current chunk to our left is not being drawn,
						// draw left edge of current block
						
						emplace_left_face(left_faces, x, y, z, type);
					}
				}

				// Right face (positive x)
				if (x == CX - 1) {
					if (m_right_chunk != nullptr) {
						if (m_right_chunk->get(0, y, z) == 0) {
							emplace_right_face(right_faces, x, y, z, type);
						}
					} else {
						emplace_right_face(right_faces, x, y, z, type);
					}
				} else {
					if (m_block_types[x + 1][y][z] == 0) {
						emplace_right_face(right_faces, x, y, z, type);
					}
				}

				// Front face (positive z)
				if (z == CZ - 1) {
					if (m_front_chunk != nullptr) {
						if (m_front_chunk->get(x, y, 0) == 0) {
							emplace_front_face(front_faces, x, y, z, type);
						}
					} else {
						emplace_front_face(front_faces, x, y, z, type);
					}
				} else {
					if (m_block_types[x][y][z + 1] == 0) {
						emplace_front_face(front_faces, x, y, z, type);
					}
				}

				// Back face (negative z)
				if (z == 0) {
					if (m_back_chunk != nullptr) {
						if (m_back_chunk->get(x, y, CZ - 1) == 0) {
							emplace_back_face(back_faces, x, y, z, type);
						}
					} else {
						emplace_back_face(back_faces, x, y, z, type);
					}
				} else {
					if (m_block_types[x][y][z - 1] == 0) {
						emplace_back_face(back_faces, x, y, z, type);
					}
				}

				// Top face (positive y)
				if (y == CY - 1) {
					if (m_top_chunk != nullptr) {
						if (m_top_chunk->get(x, 0, z) == 0) {
							emplace_top_face(top_faces, x, y, z, type);
						}
					} else {
						emplace_top_face(top_faces, x, y, z, type);
					}
				} else {
					if (m_block_types[x][y + 1][z] == 0) {
						emplace_top_face(top_faces, x, y, z, type);
					}
				}

				// Bottom face (negative y)
				if (y == 0) {
					if (m_bottom_chunk != nullptr) {
						if (m_bottom_chunk->get(x, CY - 1, z) == 0) {
							emplace_bottom_face(bottom_faces, x, y, z, type);
						}
					} else {
						emplace_bottom_face(bottom_faces, x, y, z, type);
					}
				} else {
					if (m_block_types[x][y - 1][z] == 0) {
						emplace_bottom_face(bottom_faces, x, y, z, type);
					}
				}

			}
		}
	}

	const std::vector<VertexAndNormals> meshed_faces = GreedyMeshExecutor::run_greedy_mesh(left_faces, right_faces, top_faces, bottom_faces, front_faces, back_faces);
	m_vertex_qty = static_cast<int>(meshed_faces.size());
	return meshed_faces;
}

void Chunk::emplace_left_face(std::vector<VertexAndNormals> & vertex, signed char x, signed char y, signed char z, signed char type) {
	vertex.emplace_back(x, y,     z,     type, -1, 0, 0); // bottom left
	vertex.emplace_back(x, y,     z + 1, type, -1, 0, 0); // bottom right
	vertex.emplace_back(x, y + 1, z,     type, -1, 0, 0); // top left
	vertex.emplace_back(x, y + 1, z,     type, -1, 0, 0); // top left
	vertex.emplace_back(x, y,     z + 1, type, -1, 0, 0); // bottom right
	vertex.emplace_back(x, y + 1, z + 1, type, -1, 0, 0); // top right
}

void Chunk::emplace_right_face(std::vector<VertexAndNormals> & vertex, signed char x, signed char y, signed char z, signed char type) {	
	vertex.emplace_back(x + 1, y,     z + 1, type, 1, 0, 0); // bottom left
	vertex.emplace_back(x + 1, y,     z,     type, 1, 0, 0); // bottom right
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 1, 0, 0); // top left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 1, 0, 0); // top left
	vertex.emplace_back(x + 1, y,     z,     type, 1, 0, 0); // bottom right
	vertex.emplace_back(x + 1, y + 1, z,     type, 1, 0, 0); // top right
}

void Chunk::emplace_front_face(std::vector<VertexAndNormals> & vertex, signed char x, signed char y, signed char z, signed char type) {
	vertex.emplace_back(x,     y,     z + 1, type, 0, 0, 1); // bottom left
	vertex.emplace_back(x + 1, y,     z + 1, type, 0, 0, 1); // bottom right
	vertex.emplace_back(x,     y + 1, z + 1, type, 0, 0, 1); // top left
	vertex.emplace_back(x,     y + 1, z + 1, type, 0, 0, 1); // top left
	vertex.emplace_back(x + 1, y,     z + 1, type, 0, 0, 1); // bottom right
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 0, 1); // top right
}

void Chunk::emplace_back_face(std::vector<VertexAndNormals> & vertex, signed char x, signed char y, signed char z, signed char type) {
	vertex.emplace_back(x + 1, y,     z,     type, 0, 0, -1); // bottom left
	vertex.emplace_back(x,     y,     z,     type, 0, 0, -1); // bottom right
	vertex.emplace_back(x + 1, y + 1, z,     type, 0, 0, -1); // top left
	vertex.emplace_back(x + 1, y + 1, z,     type, 0, 0, -1); // top left
	vertex.emplace_back(x,     y,     z,     type, 0, 0, -1); // bottom right
	vertex.emplace_back(x,     y + 1, z,     type, 0, 0, -1); // top right
}

void Chunk::emplace_top_face(std::vector<VertexAndNormals> & vertex, signed char x, signed char y, signed char z, signed char type) {
	vertex.emplace_back(x,     y + 1, z + 1, type, 0, 1, 0); // bottom left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 1, 0); // bottom right
	vertex.emplace_back(x,     y + 1, z,     type, 0, 1, 0); // top left
	vertex.emplace_back(x,     y + 1, z,     type, 0, 1, 0); // top left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 1, 0); // bottom right
	vertex.emplace_back(x + 1, y + 1, z,     type, 0, 1, 0); // top right
}

void Chunk::emplace_bottom_face(std::vector<VertexAndNormals> & vertex, signed char x, signed char y, signed char z, signed char type) {
	vertex.emplace_back(x,     y,     z,     type, 0, -1, 0); // bottom left
	vertex.emplace_back(x + 1, y,     z,     type, 0, -1, 0); // bottom right
	vertex.emplace_back(x,     y,     z + 1, type, 0, -1, 0); // top left
	vertex.emplace_back(x,     y,     z + 1, type, 0, -1, 0); // top left
	vertex.emplace_back(x + 1, y,     z,     type, 0, -1, 0); // bottom right
	vertex.emplace_back(x + 1, y,     z + 1, type, 0, -1, 0); // top right
}

void Chunk::print_world_position(const WorldPosition& starting_world_position) const {
	Print::print("World Position: " + std::to_string(starting_world_position.x) + ";" +
		std::to_string(starting_world_position.y) + ";" +
		std::to_string(starting_world_position.z));
}

void Chunk::set_left_chunk(const std::shared_ptr<Chunk>& chunk) {
	m_left_chunk = chunk;
}

void Chunk::set_right_chunk(const std::shared_ptr<Chunk>& chunk) {
	m_right_chunk = chunk;
}

void Chunk::set_top_chunk(const std::shared_ptr<Chunk>& chunk) {
	m_top_chunk = chunk;
}

void Chunk::set_bottom_chunk(const std::shared_ptr<Chunk>& chunk) {
	m_bottom_chunk = chunk;
}

void Chunk::set_front_chunk(const std::shared_ptr<Chunk>& chunk) {
	m_front_chunk = chunk;
}

void Chunk::set_back_chunk(const std::shared_ptr<Chunk>& chunk) {
	m_back_chunk = chunk;
}