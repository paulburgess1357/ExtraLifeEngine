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
	//Print::print("World Position: " + std::to_string(starting_world_position.x) + ";" + std::to_string(starting_world_position.y) + ";" + std::to_string(starting_world_position.z));
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
	//Print::print("Initializing Types to RANDOM 1 or 0 FOR TESTING");
	for (signed char x = 0; x < CX; x++) {
		for (signed char y = 0; y < CY; y++) {
			for (signed char z = 0; z < CZ; z++) {
				int RANDOMVALUE = rand() % 3;

				//if(RANDOMVALUE <= 0){
				//	m_block_types[x][y][z] = 0;
				//} else{
				//	m_block_types[x][y][z] = 1;
				//}
				
				m_block_types[x][y][z] = RANDOMVALUE;
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
	vertex.emplace_back(x,     y,     z + 1, type, 0, 0, 1); // bottom left
	vertex.emplace_back(x + 1, y,     z + 1, type, 0, 0, 1); // bottom right
	vertex.emplace_back(x,     y + 1, z + 1, type, 0, 0, 1); // top left
	vertex.emplace_back(x,     y + 1, z + 1, type, 0, 0, 1); // top left
	vertex.emplace_back(x + 1, y,     z + 1, type, 0, 0, 1); // bottom right
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 0, 1); // top right
}

void IChunk::emplace_back_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type){
	vertex.emplace_back(x + 1, y,     z,     type, 0, 0, -1); // bottom left
	vertex.emplace_back(x,     y,     z,     type, 0, 0, -1); // bottom right
	vertex.emplace_back(x + 1, y + 1, z,     type, 0, 0, -1); // top left
	vertex.emplace_back(x + 1, y + 1, z,     type, 0, 0, -1); // top left
	vertex.emplace_back(x,     y,     z,     type, 0, 0, -1); // bottom right
	vertex.emplace_back(x,     y + 1, z,     type, 0, 0, -1); // top right
}

void IChunk::emplace_top_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type){
	vertex.emplace_back(x,     y + 1, z + 1, type, 0, 1, 0); // bottom left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 1, 0); // bottom right
	vertex.emplace_back(x,     y + 1, z,     type, 0, 1, 0); // top left
	vertex.emplace_back(x,     y + 1, z,     type, 0, 1, 0); // top left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 1, 0); // bottom right
	vertex.emplace_back(x + 1, y + 1, z,     type, 0, 1, 0); // top right
}

void IChunk::emplace_bottom_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type){
	vertex.emplace_back(x,     y,     z,     type, 0, -1, 0); // bottom left
	vertex.emplace_back(x + 1, y,     z,     type, 0, -1, 0); // bottom right
	vertex.emplace_back(x,     y,     z + 1, type, 0, -1, 0); // top left
	vertex.emplace_back(x,     y,     z + 1, type, 0, -1, 0); // top left
	vertex.emplace_back(x + 1, y,     z,     type, 0, -1, 0); // bottom right
	vertex.emplace_back(x + 1, y,     z + 1, type, 0, -1, 0); // top right
}

std::vector<VertexAndNormals> IChunk::merge_left_faces(std::vector<VertexAndNormals>& vertex){
	
	// Six vertices per face;  If the total number of vertices is <= 6 there is
	// no need to attempt the merge as we only have one face
	if (vertex.size() <= 6) {
		return vertex;
	};

	std::vector<VertexAndNormals> merged_vector;

	// Push back first face; This becomes our 'start' face
	merged_vector.push_back(vertex.at(0));
	merged_vector.push_back(vertex.at(1));
	merged_vector.push_back(vertex.at(2));
	merged_vector.push_back(vertex.at(3));
	merged_vector.push_back(vertex.at(4));
	merged_vector.push_back(vertex.at(5));

	// Iterate over all faces (ignoring the first face) and merge
	// Increment by 6 as each face as 6 vertices
	//
	//TODO
	//TODO Merging is not quire right.  I *think* i am merging across empty faces.  Since I don't store empty faces in the original vertex,
	//TODO its causing me to merge faces across the empty face since it looks like this in the vector:
	//TODO vector: face1, face2, face3, etc
	//TODO when really its like this:
	//TODO vector: face1, face2, empty face, face 3, etc....
	//TODO the way its implementsd now would merge all faces, when really it hsould only merge face 1 and 2.
	for(size_t i = 6; i < vertex.size(); i+=6){
		
		// Requirements to merge face:
		// Same type, x, and y (for now)
		const size_t merged_vector_size = merged_vector.size();
		
		const VertexAndNormals start_bottom_left = merged_vector.at(merged_vector_size - 6);
		const VertexAndNormals next_bottom_left = vertex.at(i);

		const bool types_match = start_bottom_left.m_w == next_bottom_left.m_w;
		const bool heights_match = start_bottom_left.m_y == next_bottom_left.m_y;
		const bool x_match = start_bottom_left.m_x == next_bottom_left.m_x;

		if(types_match && heights_match && x_match){

			// Replace current 'start face' with the merged start face
			
			// Merge
			// merged_vector.at() = merged_vector.at(merged_vector_size - 6); // Start bottom left
			merged_vector.at(merged_vector_size - 5) = vertex.at(i + 1);      // Next bottom right
			// merged_vector.at() = merged_vector.at(merged_vector_size - 4); // Start top left
			// merged_vector.at() = merged_vector.at(merged_vector_size - 3); // Start top left
			merged_vector.at(merged_vector_size - 2) = vertex.at(i + 1);      // Next bottom right
			merged_vector.at(merged_vector_size - 1) = vertex.at(i + 5);      // Next top right
						
		} else {

			// Types do not match.  Push back current face into merged vector
			merged_vector.push_back(vertex.at(i));
			merged_vector.push_back(vertex.at(i + 1));
			merged_vector.push_back(vertex.at(i + 2));
			merged_vector.push_back(vertex.at(i + 3));
			merged_vector.push_back(vertex.at(i + 4));
			merged_vector.push_back(vertex.at(i + 5));
		}
		
	}

	return merged_vector;

}
