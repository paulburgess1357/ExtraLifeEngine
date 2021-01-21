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

void IChunk::emplace_left_face(std::vector<VertexAndNormals> & vertex, signed char x, signed char y, signed char z, signed char type) {
	vertex.emplace_back(x, y, z, type, -1, 0, 0); // bottom left
	vertex.emplace_back(x, y, z + 1, type, -1, 0, 0); // bottom right
	vertex.emplace_back(x, y + 1, z, type, -1, 0, 0); // top left
	vertex.emplace_back(x, y + 1, z, type, -1, 0, 0); // top left
	vertex.emplace_back(x, y, z + 1, type, -1, 0, 0); // bottom right
	vertex.emplace_back(x, y + 1, z + 1, type, -1, 0, 0); // top right
}

void IChunk::emplace_right_face(std::vector<VertexAndNormals> & vertex, signed char x, signed char y, signed char z, signed char type) {
	vertex.emplace_back(x + 1, y, z + 1, type, 1, 0, 0); // bottom left
	vertex.emplace_back(x + 1, y, z, type, 1, 0, 0); // bottom right
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 1, 0, 0); // top left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 1, 0, 0); // top left
	vertex.emplace_back(x + 1, y, z, type, 1, 0, 0); // bottom right
	vertex.emplace_back(x + 1, y + 1, z, type, 1, 0, 0); // top right
}

void IChunk::emplace_front_face(std::vector<VertexAndNormals> & vertex, signed char x, signed char y, signed char z, signed char type) {
	vertex.emplace_back(x, y, z + 1, type, 0, 0, 1); // bottom left
	vertex.emplace_back(x + 1, y, z + 1, type, 0, 0, 1); // bottom right
	vertex.emplace_back(x, y + 1, z + 1, type, 0, 0, 1); // top left
	vertex.emplace_back(x, y + 1, z + 1, type, 0, 0, 1); // top left
	vertex.emplace_back(x + 1, y, z + 1, type, 0, 0, 1); // bottom right
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 0, 1); // top right
}

void IChunk::emplace_back_face(std::vector<VertexAndNormals> & vertex, signed char x, signed char y, signed char z, signed char type) {
	vertex.emplace_back(x + 1, y, z, type, 0, 0, -1); // bottom left
	vertex.emplace_back(x, y, z, type, 0, 0, -1); // bottom right
	vertex.emplace_back(x + 1, y + 1, z, type, 0, 0, -1); // top left
	vertex.emplace_back(x + 1, y + 1, z, type, 0, 0, -1); // top left
	vertex.emplace_back(x, y, z, type, 0, 0, -1); // bottom right
	vertex.emplace_back(x, y + 1, z, type, 0, 0, -1); // top right
}

void IChunk::emplace_top_face(std::vector<VertexAndNormals> & vertex, signed char x, signed char y, signed char z, signed char type) {
	vertex.emplace_back(x, y + 1, z + 1, type, 0, 1, 0); // bottom left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 1, 0); // bottom right
	vertex.emplace_back(x, y + 1, z, type, 0, 1, 0); // top left
	vertex.emplace_back(x, y + 1, z, type, 0, 1, 0); // top left
	vertex.emplace_back(x + 1, y + 1, z + 1, type, 0, 1, 0); // bottom right
	vertex.emplace_back(x + 1, y + 1, z, type, 0, 1, 0); // top right
}

void IChunk::emplace_bottom_face(std::vector<VertexAndNormals> & vertex, signed char x, signed char y, signed char z, signed char type) {
	vertex.emplace_back(x, y, z, type, 0, -1, 0); // bottom left
	vertex.emplace_back(x + 1, y, z, type, 0, -1, 0); // bottom right
	vertex.emplace_back(x, y, z + 1, type, 0, -1, 0); // top left
	vertex.emplace_back(x, y, z + 1, type, 0, -1, 0); // top left
	vertex.emplace_back(x + 1, y, z, type, 0, -1, 0); // bottom right
	vertex.emplace_back(x + 1, y, z + 1, type, 0, -1, 0); // top right
}

std::vector<VertexAndNormals> IChunk::merge_left_faces(std::vector<VertexAndNormals> & vertex) {

	//TODO i can adjust this.  I don't have to merge each time.  I think I can
	//TODO continue iterating across the faces until I can't include a block.
	//TODO when I reach that point, I do the merge.  This would save some time
	//TODO as I can do one merge only when its more than 2 blocks.  For example.
	//TODO if it was 6 blocks, that would be five merges.  However, if I do it
	//TODO more efficient, I can do that in one merge.  I jsut have to mkae sure
	//TODO blocks are the same type and sequential in between


	// Six vertices per face;  If the total number of vertices is <= 6 there is
	// no need to attempt the merge as we only have one face
	if (vertex.size() <= 6) {
		return vertex;
	};

	std::vector<VertexAndNormals> merged_row_vector;

	// Push back first face; This becomes our 'start' face
	merged_row_vector.push_back(vertex.at(0));
	merged_row_vector.push_back(vertex.at(1));
	merged_row_vector.push_back(vertex.at(2));
	merged_row_vector.push_back(vertex.at(3));
	merged_row_vector.push_back(vertex.at(4));
	merged_row_vector.push_back(vertex.at(5));

	// Iterate over all faces (ignoring the first face) and merge
	// Increment by 6 as each face as 6 vertices
	for (size_t i = 6; i < vertex.size(); i += 6) {

		// Requirements to merge face:
		// Same type, x, and y (for now)
		const size_t merged_vector_size = merged_row_vector.size();

		const VertexAndNormals start_bottom_right = merged_row_vector.at(merged_vector_size - 5);
		const VertexAndNormals next_bottom_right = vertex.at(i + 1);

		const bool types_match = start_bottom_right.m_w == next_bottom_right.m_w;;
		const bool heights_match = start_bottom_right.m_y == next_bottom_right.m_y;
		const bool x_match = start_bottom_right.m_x == next_bottom_right.m_x;

		// Compare bottom right to ensure the start square and next square are
		// 'next' to each other. If they aren't, it means we are at an
		// 'empty block', and so we can't merge across it.  This can be
		// compared by checking the 'bottom right' of the current block and
		// next block. If they are next to each other, they will be within 1 of
		// each other.
		const bool adjacent_faces = start_bottom_right.m_z == next_bottom_right.m_z - 1;

		if (types_match && heights_match && x_match && adjacent_faces) {

			// Merge faces.  On the next iteration, our 'start face' will be
			// this merged face.

			// Merge (note that we only need to merge the 'next' face
			// into our 'start face' slot.  Rather than putting all 6 new
			// faces into the vector, we only need the 3 new ones:
			
			merged_row_vector.at(merged_vector_size - 5) = vertex.at(i + 1);      // Next bottom right
			merged_row_vector.at(merged_vector_size - 2) = vertex.at(i + 1);      // Next bottom right
			merged_row_vector.at(merged_vector_size - 1) = vertex.at(i + 5);      // Next top right

		} else {

			// Faces cannot be merged. Push back current face into merged
			// vector. This becomes the new 'start face'
			merged_row_vector.push_back(vertex.at(i));
			merged_row_vector.push_back(vertex.at(i + 1));
			merged_row_vector.push_back(vertex.at(i + 2));
			merged_row_vector.push_back(vertex.at(i + 3));
			merged_row_vector.push_back(vertex.at(i + 4));
			merged_row_vector.push_back(vertex.at(i + 5));
		}

	}

	return(merged_row_vector);

	// TODO make sure i can do my face 'type' comparisons correctly...
	// TODO I think I can...
	
	// Faces have now been merged per row.  Now we can compare
	// the merged faces across the y axis.  If x and z are identical for 2
	// faces, we can merge upward.

	if(merged_row_vector.size() <= 6){
		return merged_row_vector;
	}

	std::vector<VertexAndNormals> merged_y_vector;
	//merged_y_vector.push_back(merged_row_vector.at(0));
	//merged_y_vector.push_back(merged_row_vector.at(1));
	//merged_y_vector.push_back(merged_row_vector.at(2));
	//merged_y_vector.push_back(merged_row_vector.at(3));
	//merged_y_vector.push_back(merged_row_vector.at(4));
	//merged_y_vector.push_back(merged_row_vector.at(5));
	
	// Keep track of merged faces.  If a face has been merged, we can skip it
	std::vector<bool> has_been_merged (merged_row_vector.size(), false );

	for(size_t i = 0; i < merged_row_vector.size(); i+=6){

		// Check if face has been merged.  If it has, we can skip to the next face
		if (has_been_merged.at(i)) {
			continue;
		}
		
		bool face_can_merge = false;
		VertexAndNormals next_top_left;
		VertexAndNormals next_top_right;
		
		const size_t start_bottom_left_idx = i;
		const size_t start_bottom_right_idx = i + 1;
		const size_t start_top_left_idx = i + 2;
		const size_t start_top_left_idx_second = i + 3;
		const size_t start_bottom_right_idx_second = i + 4;
		const size_t start_top_right_idx = i + 5;

		const VertexAndNormals start_bottom_left = merged_row_vector.at(start_bottom_left_idx);
		const VertexAndNormals start_bottom_right = merged_row_vector.at(start_bottom_right_idx);
		VertexAndNormals start_top_left = merged_row_vector.at(start_top_left_idx);
		VertexAndNormals start_top_right = merged_row_vector.at(start_top_right_idx);
		const signed char start_type = start_bottom_left.m_w;


		for(size_t j = i + 6; j < merged_row_vector.size(); j+=6){

			const size_t next_bottom_left_idx = j;
			const size_t next_bottom_right_idx = j + 1;
			const size_t next_top_left_idx = j + 2;
			const size_t next_top_right_idx = j + 5;

			// Next face (to see if we can merge)
			const VertexAndNormals next_bottom_left = merged_row_vector.at(next_bottom_left_idx);
			const VertexAndNormals next_bottom_right = merged_row_vector.at(next_bottom_right_idx);
			next_top_left = merged_row_vector.at(next_top_left_idx);
			next_top_right = merged_row_vector.at(next_top_right_idx);
			const signed char next_type = next_bottom_left.m_w;

			// Merged faces must be the same type.  If the start face and
			// next face are not the same type, we can continue on to the
			// next 'next' face
			if(start_type != next_type){
				continue;
			}
			
			// Check if face has been merged.  If it has, we can skip to the next face
			if(has_been_merged.at(next_bottom_left_idx)){
				continue;
			}

			// Check is we are at the same depth (x) as our start face.  If
			// we are not at the same depth, faces cannot be merged and we can
			// break out of the 'look for faces to merge' loop
			if(start_bottom_left.m_x != next_bottom_left.m_x){
				break;
			}
			
			// Check if start face and next face are adjacent (y).  This is
			// the top of the start face and bottom of the next face.  If they
			// are not adjacent (y), move on to the next 'next' face
			if (start_top_right.m_y > next_bottom_right.m_y) {
				continue;
			}

			// Check if the start face and next are within one row of each
			// other if they aren't, it means we are above the necessary row
			// for merging and can break from the loop
			if (start_top_right.m_y < next_bottom_right.m_y) {
				break;
			}

			// At this point, the start face and next face must be adjacent
			// in the 'y' direction.  Before merging, we must check if the
			// both corners are aligned:

			// If the 'next' block (which is above us at this point),
			// left corner is greater than the start block left corner,
			// there are no faces left to merge
			if (next_bottom_left.m_z > start_bottom_left.m_z) {
				break;
			}

			// If the next block and current block are aligned then merge:
			if(start_bottom_left.m_z == next_bottom_left.m_z && start_bottom_right.m_z == next_bottom_right.m_z){
				
				// Update start variables
				start_top_left = next_top_left;
				start_top_right = next_top_right;

				// Flag merge vector (Allows us to skip this face for
				// consideration of future merges)
				has_been_merged.at(next_bottom_left_idx) = true;
				face_can_merge = true;
			}
			
		}

		// If we have exited the inner loop, its either because a face was
		// merged or not.
		if(face_can_merge){
			merged_y_vector.push_back(start_bottom_left);
			merged_y_vector.push_back(start_bottom_right);
			merged_y_vector.push_back(next_top_left);
			merged_y_vector.push_back(next_top_left);
			merged_y_vector.push_back(start_bottom_right);
			merged_y_vector.push_back(next_top_right);

		} else{
			merged_y_vector.push_back(start_bottom_left);
			merged_y_vector.push_back(start_bottom_right);
			merged_y_vector.push_back(start_top_left);
			merged_y_vector.push_back(start_top_left);
			merged_y_vector.push_back(start_bottom_right);
			merged_y_vector.push_back(start_top_right);
		}
						
	}			

	return merged_y_vector;

}
