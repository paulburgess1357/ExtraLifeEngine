#include "IChunk.h"
#include "../../Utility/Print.h"
#include "../../Matrix/MatrixFunctions.h"
#include <glm/gtc/matrix_transform.hpp>

IChunk::IChunk(const WorldPosition& starting_world_position,
	const std::shared_ptr<IShaderProgram>& shader_program)
	:m_block_types{},
	m_vertex_qty{ 0 },
	m_update_required{ true },
	m_model_matrix{ glm::translate(glm::mat4(1), starting_world_position.get_vec3()) },
	m_normal_matrix{ MatrixFunctions::get_normal_matrix(m_model_matrix) },
    m_world_position{ starting_world_position },
	m_shader_program{ shader_program }{
	initialize_types();
	Print::print("World Position: " + std::to_string(starting_world_position.x) + ";" + std::to_string(starting_world_position.y) + ";" + std::to_string(starting_world_position.z));
}

IChunk::~IChunk() = default;

signed char IChunk::get(const signed char x, const signed char y, const signed char z) const {
	return m_block_types[x][y][z];
}

void IChunk::set(const signed char x, const signed char y, const signed char z, const signed char type) {
	m_block_types[x][y][z] = type;
	m_update_required = true;
}

void IChunk::initialize_types() {
	Print::print("Initializing Types to RANDOM 1 or 0 FOR TESTING");
	for (signed char x = 0; x < CX; x++) {
		for (signed char y = 0; y < CY; y++) {
			for (signed char z = 0; z < CZ; z++) {
				int RANDOMVALUE = rand() % 10;

				if(RANDOMVALUE <= 0){
					m_block_types[x][y][z] = 0;
				} else{
					m_block_types[x][y][z] = 1;
				}
				
				//m_block_types[x][y][z] = RANDOMVALUE;
			}
		}
	}
}

void IChunk::emplace_left_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type){
	vertex.emplace_back(x,     y,     z,     type, -1, 0, 0); // bottom left
	vertex.emplace_back(x,     y,     z + 1, type, -1, 0, 0); // bottom right
	vertex.emplace_back(x,     y + 1, z,     type, -1, 0, 0); // top left
	vertex.emplace_back(x,     y + 1, z,     type, -1, 0, 0); // top left
	vertex.emplace_back(x,     y,     z + 1, type, -1, 0, 0); // bottom right
	vertex.emplace_back(x,     y + 1, z + 1, type, -1, 0, 0); // top right
}

void IChunk::emplace_right_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type){
	vertex.emplace_back(x + 1, y,     z + 1, type, 1, 0, 0); // bottom left
	vertex.emplace_back(x + 1, y,     z,     type, 1, 0, 0); // bottom right
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 1, 0, 0); // top left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 1, 0, 0); // top left
	vertex.emplace_back(x + 1, y,     z,     type, 1, 0, 0); // bottom right
	vertex.emplace_back(x + 1, y + 1, z,     type, 1, 0, 0); // top right
}

void IChunk::emplace_front_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type){
	vertex.emplace_back(x, y, z + 1, type, 0, 0, 1); // bottom left
	vertex.emplace_back(x + 1, y, z + 1, type, 0, 0, 1); // bottom right
	vertex.emplace_back(x, y + 1, z + 1, type, 0, 0, 1); // top left
	vertex.emplace_back(x, y + 1, z + 1, type, 0, 0, 1); // top left
	vertex.emplace_back(x + 1, y, z + 1, type, 0, 0, 1); // bottom right
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 0, 1); // top right
}

void IChunk::emplace_back_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type){
	vertex.emplace_back(x + 1, y, z, type, 0, 0, -1); // bottom left
	vertex.emplace_back(x, y, z, type, 0, 0, -1); // bottom right
	vertex.emplace_back(x + 1, y + 1, z, type, 0, 0, -1); // top left
	vertex.emplace_back(x + 1, y + 1, z, type, 0, 0, -1); // top left
	vertex.emplace_back(x, y, z, type, 0, 0, -1); // bottom right
	vertex.emplace_back(x, y + 1, z, type, 0, 0, -1); // top right
}



void IChunk::emplace_top_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type){
	vertex.emplace_back(x, y + 1, z + 1, type, 0, 1, 0); // bottom left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 1, 0); // bottom right
	vertex.emplace_back(x, y + 1, z, type, 0, 1, 0); // top left
	vertex.emplace_back(x, y + 1, z, type, 0, 1, 0); // top left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 1, 0); // bottom right
	vertex.emplace_back(x + 1, y + 1, z, type, 0, 1, 0); // top right
}

void IChunk::emplace_bottom_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type){
	vertex.emplace_back(x, y, z, type, 0, -1, 0); // bottom left
	vertex.emplace_back(x + 1, y, z, type, 0, -1, 0); // bottom right
	vertex.emplace_back(x, y, z + 1, type, 0, -1, 0); // top left
	vertex.emplace_back(x, y, z + 1, type, 0, -1, 0); // top left
	vertex.emplace_back(x + 1, y, z, type, 0, -1, 0); // bottom right
	vertex.emplace_back(x + 1, y, z + 1, type, 0, -1, 0); // top right
}


