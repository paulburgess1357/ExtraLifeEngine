#include "Chunk.h"
#include "../Neutral/TerrainGeneration.h"
#include "../GreedyMesh/GreedyMeshExecutor.h"
#include "../../Utility/Print.h"

Chunk::Chunk(const WorldPosition& starting_world_position)
	:m_vertex_qty{ 0 },
	m_update_required{ true },
	m_block_types{},
	m_starting_world_position{ starting_world_position } {
	initialize_types();	
}

Chunk::~Chunk() = default;

void Chunk::initialize_types() {

	// This shouldn't impact the chunk optimizations because the LOAD order
	// is the same.  The block types are set before loading.  This means the
	// direction of the faces is the same.
	
	for (int x = 0; x < x_block_qty; x++) {
		for (int z = 0; z < z_block_qty; z++) {

			//int RANDOMVALUE = rand() % 2;
			//if(RANDOMVALUE == 0){
			//	RANDOMVALUE = 1;
			//}
			
			const int height = TerrainGeneration::generate_top_layer(m_starting_world_position, x, z, x_block_qty, y_block_qty, z_block_qty);

			for(int y = 0; y < height; y++){
				set_block_type(x, y, z, 1);
			}

		}
	}
			
}

void Chunk::set_block_type(const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type) {
	m_block_types[x][y][z] = type;
	m_update_required = true;
}

unsigned char Chunk::get_block_type(const unsigned char x, const unsigned char y, const unsigned char z) const {
	return m_block_types[x][y][z];
}

void Chunk::set_left_adjacent_chunk(const std::shared_ptr<Chunk>& chunk) {
	m_left_chunk = chunk;
}

void Chunk::set_right_adjacent_chunk(const std::shared_ptr<Chunk>& chunk) {
	m_right_chunk = chunk;
}

void Chunk::set_top_adjacent_chunk(const std::shared_ptr<Chunk>& chunk) {
	m_top_chunk = chunk;
}

void Chunk::set_bottom_adjacent_chunk(const std::shared_ptr<Chunk>& chunk) {
	m_bottom_chunk = chunk;
}

void Chunk::set_front_adjacent_chunk(const std::shared_ptr<Chunk>& chunk) {
	m_front_chunk = chunk;
}

void Chunk::set_back_adjacent_chunk(const std::shared_ptr<Chunk>& chunk) {
	m_back_chunk = chunk;
}

bool Chunk::is_empty() const{
	if(m_vertex_qty == 0){
		return true;
	}
	return false;
}

std::vector<VertexAndNormals> Chunk::load_chunk_data() {

	// When creating chunks larger than 15x15x15 a vector is required.
	// It is possible to create this vertex using:
	// VertexAndNormals vertex[x_block_qty * y_block_qty * z_block_qty * 6 * 6]
	// However, this is created on the stack and you will quickly run into
	// memory issues when creating chunks larger than 15x15x15.

	// Split voxels into separate faces for greedy meshing:
	std::vector<VertexAndNormals> left_faces;
	std::vector<VertexAndNormals> right_faces;
	std::vector<VertexAndNormals> top_faces;
	std::vector<VertexAndNormals> bottom_faces;
	std::vector<VertexAndNormals> front_faces;
	std::vector<VertexAndNormals> back_faces;

	for (unsigned char x = 0; x < x_block_qty; x++) {
		for (unsigned char y = 0; y < y_block_qty; y++) {
			for (unsigned char z = 0; z < z_block_qty; z++) {
				const unsigned char type = m_block_types[x][y][z];

				// Skip Empty Blocks
				if (type == 0) {
					continue;
				}

				load_left_face(left_faces, x, y, z, type);
				load_right_face(right_faces, x, y, z, type);
				load_front_face(front_faces, x, y, z, type);
				load_back_face(back_faces, x, y, z, type);
				load_top_face(top_faces, x, y, z, type);
				load_bottom_face(bottom_faces, x, y, z, type);
			}
		}
	}

	const std::vector<VertexAndNormals> meshed_faces = GreedyMeshExecutor::run_greedy_mesh(left_faces, right_faces, top_faces, bottom_faces, front_faces, back_faces);
	m_vertex_qty = static_cast<int>(meshed_faces.size());
	return meshed_faces;
}

void Chunk::load_left_face(std::vector<VertexAndNormals>& left_faces, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type){

	// The following description applies to all faces

	// Left face (negative x)
	if (x == 0) {
		if (m_left_chunk != nullptr) {
			
			// If drawing left edge of current chunk and there exists a chunk to our left:
			// Check edge of adjacent chunk (right edge)
			// If the adjacent chunk right edge is not being drawn, draw left edge of current chunk
			
			if (m_left_chunk->get_block_type(x_block_qty - 1, y, z) == 0) {
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
}

void Chunk::load_right_face(std::vector<VertexAndNormals>& right_faces, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type){
	// Right face (positive x)
	if (x == x_block_qty - 1) {
		if (m_right_chunk != nullptr) {
			if (m_right_chunk->get_block_type(0, y, z) == 0) {
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
}

void Chunk::load_front_face(std::vector<VertexAndNormals>& front_faces, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type){
	// Front face (positive z)
	if (z == z_block_qty - 1) {
		if (m_front_chunk != nullptr) {
			if (m_front_chunk->get_block_type(x, y, 0) == 0) {
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
}

void Chunk::load_back_face(std::vector<VertexAndNormals>& back_faces, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type){
	// Back face (negative z)
	if (z == 0) {
		if (m_back_chunk != nullptr) {
			if (m_back_chunk->get_block_type(x, y, z_block_qty - 1) == 0) {
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
}

void Chunk::load_top_face(std::vector<VertexAndNormals>& top_faces, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type){
	// Top face (positive y)
	if (y == y_block_qty - 1) {
		if (m_top_chunk != nullptr) {
			if (m_top_chunk->get_block_type(x, 0, z) == 0) {
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
}

void Chunk::load_bottom_face(std::vector<VertexAndNormals>& bottom_faces, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type){
	// Bottom face (negative y)
	if (y == 0) {
		if (m_bottom_chunk != nullptr) {
			if (m_bottom_chunk->get_block_type(x, y_block_qty - 1, z) == 0) {
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

void Chunk::emplace_left_face(std::vector<VertexAndNormals> & vertex, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type) {
	vertex.emplace_back(x, y,     z,     type, -1, 0, 0); // bottom left
	vertex.emplace_back(x, y,     z + 1, type, -1, 0, 0); // bottom right
	vertex.emplace_back(x, y + 1, z,     type, -1, 0, 0); // top left
	vertex.emplace_back(x, y + 1, z,     type, -1, 0, 0); // top left
	vertex.emplace_back(x, y,     z + 1, type, -1, 0, 0); // bottom right
	vertex.emplace_back(x, y + 1, z + 1, type, -1, 0, 0); // top right
}

void Chunk::emplace_right_face(std::vector<VertexAndNormals> & vertex, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type) {	
	vertex.emplace_back(x + 1, y,     z + 1, type, 1, 0, 0); // bottom left
	vertex.emplace_back(x + 1, y,     z,     type, 1, 0, 0); // bottom right
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 1, 0, 0); // top left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 1, 0, 0); // top left
	vertex.emplace_back(x + 1, y,     z,     type, 1, 0, 0); // bottom right
	vertex.emplace_back(x + 1, y + 1, z,     type, 1, 0, 0); // top right
}

void Chunk::emplace_front_face(std::vector<VertexAndNormals> & vertex, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type) {
	vertex.emplace_back(x,     y,     z + 1, type, 0, 0, 1); // bottom left
	vertex.emplace_back(x + 1, y,     z + 1, type, 0, 0, 1); // bottom right
	vertex.emplace_back(x,     y + 1, z + 1, type, 0, 0, 1); // top left
	vertex.emplace_back(x,     y + 1, z + 1, type, 0, 0, 1); // top left
	vertex.emplace_back(x + 1, y,     z + 1, type, 0, 0, 1); // bottom right
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 0, 1); // top right
}

void Chunk::emplace_back_face(std::vector<VertexAndNormals> & vertex, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type) {
	vertex.emplace_back(x + 1, y,     z,     type, 0, 0, -1); // bottom left
	vertex.emplace_back(x,     y,     z,     type, 0, 0, -1); // bottom right
	vertex.emplace_back(x + 1, y + 1, z,     type, 0, 0, -1); // top left
	vertex.emplace_back(x + 1, y + 1, z,     type, 0, 0, -1); // top left
	vertex.emplace_back(x,     y,     z,     type, 0, 0, -1); // bottom right
	vertex.emplace_back(x,     y + 1, z,     type, 0, 0, -1); // top right
}

void Chunk::emplace_top_face(std::vector<VertexAndNormals> & vertex, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type) {
	vertex.emplace_back(x,     y + 1, z + 1, type, 0, 1, 0); // bottom left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 1, 0); // bottom right
	vertex.emplace_back(x,     y + 1, z,     type, 0, 1, 0); // top left
	vertex.emplace_back(x,     y + 1, z,     type, 0, 1, 0); // top left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 1, 0); // bottom right
	vertex.emplace_back(x + 1, y + 1, z,     type, 0, 1, 0); // top right
}

void Chunk::emplace_bottom_face(std::vector<VertexAndNormals> & vertex, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type) {
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

int Chunk::get_vertex_qty() const{
	return m_vertex_qty;
}

bool Chunk::update_required() const{
	return m_update_required;
}

WorldPosition Chunk::get_starting_world_position() const {
	return m_starting_world_position;
}

void Chunk::set_update_required(const bool update_required){
	m_update_required = update_required;
}