#include "GreedyMesh.h"

std::vector<VertexAndNormals> GreedyMesh::rowwise_merge_faces(const std::vector<VertexAndNormals>& vertex, const FaceType face_type){

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
	pushback_face(merged_row_vector, get_face(vertex, 0));

	// Iterate over all faces (ignoring the first face) and merge
	// Increment by 6 as each face as 6 vertices
	for (size_t i = 6; i < vertex.size(); i += 6) {

		const Face start_face = get_face(merged_row_vector, merged_row_vector.size() - 6);
		const Face next_face = get_face(vertex, i);

		// Merge faces of possible.  Regardless if its possible or not,
		// the last face in the merged_row_vector becomes our new start face
		if (rowwise_is_mergeable(start_face, next_face, face_type)) {			
			rowwise_merge(merged_row_vector, next_face, face_type, i);
		} else {
			pushback_face(merged_row_vector, next_face);
		}

	}

	return(merged_row_vector);	
}

void GreedyMesh::rowwise_merge(std::vector<VertexAndNormals>& merged_vector, const Face& next_face, const FaceType face_type, const size_t start_idx){

	// Merge (note that we only need to merge the 'next' face
	// into our 'start face' slot.  Rather than putting all 6 new
	// faces into the vector, we only need the 3 new ones:
	
	switch (face_type) {

	case FaceType::LEFT: {
		
		const size_t merged_vector_size = merged_vector.size();
		merged_vector.at(merged_vector_size - 5) = next_face.get_bottom_right();      
		merged_vector.at(merged_vector_size - 2) = next_face.get_bottom_right();
		merged_vector.at(merged_vector_size - 1) = next_face.get_top_right();
		break;
	}

	case FaceType::RIGHT: {

		break;
	}

	default: {
		break;
	}



	}
	
}

bool GreedyMesh::rowwise_adjacent_faces(const Face& start_face, const Face& next_face, const FaceType face_type){

	bool adjacent = false;
	
	switch (face_type){
		case FaceType::LEFT:{
			adjacent = start_face.get_bottom_right().m_z == next_face.get_bottom_right().m_z - 1;
			break;
		}

		default:{
			break;
		}
	}

	return adjacent;
	
}


bool GreedyMesh::rowwise_is_mergeable(const Face& start_face, const Face& next_face, const FaceType face_type){

	bool is_mergeable = false;
	
	switch (face_type) {
		case FaceType::LEFT: {
			is_mergeable = types_match(start_face, next_face) && y_match(start_face, next_face) && x_match(start_face, next_face) && rowwise_adjacent_faces(start_face, next_face, face_type);			
			break;
		}

		default: {
			break;
		}
	}

	return is_mergeable;
}

bool GreedyMesh::types_match(const Face& start_face, const Face& next_face){
	return start_face.get_type() == next_face.get_type();
}



std::vector<VertexAndNormals> GreedyMesh::across_rows_merge_faces(const std::vector<VertexAndNormals>& merged_row_vector, const FaceType face_type) {
	
	// TODO make sure i can do my face 'type' comparisons correctly...
	// TODO I think I can...

	// Faces have now been merged per row.  Now we can compare
	// the merged faces across the y axis.  If x and z are identical for 2
	// faces, we can merge upward.

	if (merged_row_vector.size() <= 6) {
		return merged_row_vector;
	}

	// Keep track of merged faces.  If a face has been merged, we can skip it
	std::vector<bool> has_been_merged(merged_row_vector.size(), false);

	std::vector<VertexAndNormals> merged_y_vector;
	for (size_t i = 0; i < merged_row_vector.size(); i += 6) {

		// Check if face has been merged.  If it has, we can skip to the next face
		if (has_been_merged.at(i)) {
			continue;
		}

		bool face_can_merge = false;

		Face start_face = get_face(merged_row_vector, i);
		Face next_face;

		for (size_t j = i + 6; j < merged_row_vector.size(); j += 6) {

			size_t face_can_merge_idx = j;
			
			// Next face (to see if we can merge)
			next_face = get_face(merged_row_vector, j);

			// Merged faces must be the same type.  If the start face and
			// next face are not the same type, we can continue on to the
			// next 'next' face
			if (!types_match(start_face, next_face)) {
				continue;
			}

			// Check if start face and next face are adjacent (y).  This is
			// the top of the start face and bottom of the next face.  If they
			// are not adjacent (y), move on to the next 'next' face
			if(!top_start_and_bottom_next_corner_same_height(start_face, next_face, face_type)){
				continue;
			}

			// If the 'next' block bottom left corner is < than
			// our bottom left corner, we can continue onto the next
			// face
			if(block_too_early(start_face, next_face, face_type)){
				continue;
			}

			// If the 'next' block (which is above us at this point),
			// left corner is greater than the start block left corner,
			// there are no faces left to merge
			if(past_merge_location(start_face, next_face, face_type)){
				break;
			}

			// Check if face has been merged.  If it has, we can skip to the next face
			if (has_been_merged.at(face_can_merge_idx)) {
				continue;
			}

			// Check is we are at the same depth (x) as our start face.  If
			// we are not at the same depth, faces cannot be merged and we can
			// break out of the 'look for faces to merge' loop
			if(!depths_match(start_face, next_face, face_type)){
				break;
			}			

			// Check if the start face and next are within one row of each
			// other if they aren't, it means we are above the necessary row
			// for merging and can break from the loop
			if (past_merge_row(start_face, next_face, face_type)) {
				break;
			}

			// At this point, the start face and next face must be adjacent
			// in the 'y' direction.  Before merging, we must check if the
			// both corners are aligned.  Note: no need to check bottom
			// left 'z' here.  They must be equal to get to this point

			if (corners_aligned(start_face, next_face, face_type)) {
				// Update start variables
				start_face.set_top_left(next_face.get_top_left());
				start_face.set_top_right(next_face.get_top_right());

				// Flag merge vector (Allows us to skip this face for
				// consideration of future merges)
				has_been_merged.at(face_can_merge_idx) = true;
				face_can_merge = true;
			}

		}

		// If we have exited the inner loop, its either because a face was
		// merged or not.
		if (face_can_merge) {

			// In the merge loop we update the 'start' top variables.
			// This allows the inner j loop to continue looking for
			// more faces after a merge.  However, when we want to
			// merge, we now need to use the updated 'start'
			// faces, because they are based on the 'next' faces that they
			// were able to merge to
			pushback_face(merged_y_vector, start_face);

		} else {
			pushback_face(merged_y_vector, start_face);
		}

	}

	return merged_y_vector;

}

bool GreedyMesh::corners_aligned(const Face& start_face, const Face& next_face, const FaceType face_type){
	bool corners_aligned = false;

	switch (face_type) {
		case FaceType::LEFT: {
			corners_aligned = z_width_match(start_face, next_face);
			//corners_aligned = start_face.get_bottom_right().m_z == next_face.get_bottom_right().m_z;
			break;
		}

		default: {
			break;
		}
	}

	return corners_aligned;
}

bool GreedyMesh::z_width_match(const Face& start_face, const Face& next_face) {
	return start_face.get_bottom_left().m_z == next_face.get_bottom_left().m_z &&
		   start_face.get_bottom_right().m_z == next_face.get_bottom_right().m_z;
}

bool GreedyMesh::past_merge_row(const Face& start_face, const Face& next_face, const FaceType face_type){
	bool past_merge_row = false;

	switch (face_type) {
		case FaceType::LEFT: {
			past_merge_row = start_face.get_top_right().m_y < next_face.get_bottom_right().m_y;
			break;
		}

		default: {
			break;
		}
	}

	return past_merge_row;
}


bool GreedyMesh::depths_match(const Face& start_face, const Face& next_face, const FaceType face_type){
	bool depth_match = false;

	switch (face_type) {
		case FaceType::LEFT: {
			depth_match = x_match(start_face, next_face);


			break;
		}

		default: {
			break;
		}
	}

	return depth_match;
}


bool GreedyMesh::block_too_early(const Face& start_face, const Face& next_face, const FaceType face_type){
	bool too_early = false;

	switch (face_type) {
		case FaceType::LEFT: {
			too_early = next_face.get_bottom_left().m_z < start_face.get_bottom_left().m_z;


			break;
		}

		default: {
			break;
		}
	}

	return too_early;
}

bool GreedyMesh::past_merge_location(const Face& start_face, const Face& next_face, const FaceType face_type){
	bool past_merge_location = false;

	switch (face_type) {
		case FaceType::LEFT: {
			past_merge_location = next_face.get_bottom_left().m_z > start_face.get_bottom_left().m_z;
			break;
		}

		default: {
			break;
		}
	}

	return past_merge_location;
}



Face GreedyMesh::get_face(const std::vector<VertexAndNormals>& vertex, const size_t start_idx){
	return Face{
		vertex.at(start_idx),     // Bottom Left
		vertex.at(start_idx + 1), // Bottom Right
		vertex.at(start_idx + 2), // Top left
		vertex.at(start_idx + 5)  // Top Right
	};
}

void GreedyMesh::pushback_face(std::vector<VertexAndNormals>& fill_vector, const Face& face){
	fill_vector.push_back(face.get_bottom_left());
	fill_vector.push_back(face.get_bottom_right());
	fill_vector.push_back(face.get_top_left());
	fill_vector.push_back(face.get_top_left());
	fill_vector.push_back(face.get_bottom_right());
	fill_vector.push_back(face.get_top_right());
}

bool GreedyMesh::y_match(const Face& start_face, const Face& next_face){
	return start_face.get_bottom_left().m_y == next_face.get_bottom_left().m_y && 
		   start_face.get_top_left().m_y == next_face.get_top_left().m_y;
}

bool GreedyMesh::x_match(const Face& start_face, const Face& next_face){
	return start_face.get_bottom_left().m_x == next_face.get_bottom_left().m_x &&
		start_face.get_top_left().m_x == next_face.get_top_left().m_x;
}



bool GreedyMesh::top_start_and_bottom_next_corner_same_height(const Face& start_face, const Face& next_face, const FaceType face_type){
	bool same_height = false;

	switch (face_type) {
	case FaceType::LEFT: {
		same_height = start_face.get_top_right().m_y == next_face.get_bottom_right().m_y;

		
		break;
	}

	default: {
		break;
	}
	}

	return same_height;
}




//std::vector<VertexAndNormals> IChunk::merge_right_faces(std::vector<VertexAndNormals>& vertex) {
//
//	//TODO i can adjust this.  I don't have to merge each time.  I think I can
//	//TODO continue iterating across the faces until I can't include a block.
//	//TODO when I reach that point, I do the merge.  This would save some time
//	//TODO as I can do one merge only when its more than 2 blocks.  For example.
//	//TODO if it was 6 blocks, that would be five merges.  However, if I do it
//	//TODO more efficient, I can do that in one merge.  I jsut have to mkae sure
//	//TODO blocks are the same type and sequential in between
//
//
//	// Six vertices per face;  If the total number of vertices is <= 6 there is
//	// no need to attempt the merge as we only have one face
//	if (vertex.size() <= 6) {
//		return vertex;
//	};
//
//	std::vector<VertexAndNormals> merged_row_vector;
//
//	// Push back first face; This becomes our 'start' face
//	merged_row_vector.push_back(vertex.at(0));
//	merged_row_vector.push_back(vertex.at(1));
//	merged_row_vector.push_back(vertex.at(2));
//	merged_row_vector.push_back(vertex.at(3));
//	merged_row_vector.push_back(vertex.at(4));
//	merged_row_vector.push_back(vertex.at(5));
//
//	// Iterate over all faces (ignoring the first face) and merge
//	// Increment by 6 as each face as 6 vertices
//	for (size_t i = 6; i < vertex.size(); i += 6) {
//
//		// Requirements to merge face:
//		// Same type, x, and y (for now)
//		const size_t merged_vector_size = merged_row_vector.size();
//
//		const VertexAndNormals start_bottom_right = merged_row_vector.at(merged_vector_size - 5);
//		const VertexAndNormals next_bottom_right = vertex.at(i + 1);
//
//		const bool rowwise_types_match = start_bottom_right.m_w == next_bottom_right.m_w;; //TODO For the right face, I think I need to change this ti the left for comparison, since those will be within one of each other
//		const bool rowwise_heights_match = start_bottom_right.m_y == next_bottom_right.m_y;
//		const bool x_match = start_bottom_right.m_x == next_bottom_right.m_x;
//
//		// Compare bottom right to ensure the start square and next square are
//		// 'next' to each other. If they aren't, it means we are at an
//		// 'empty block', and so we can't merge across it.  This can be
//		// compared by checking the 'bottom right' of the current block and
//		// next block. If they are next to each other, they will be within 1 of
//		// each other.
//		const bool rowwise_adjacent_faces = start_bottom_right.m_z == next_bottom_right.m_z - 1; // this doesn't work for right face comparison!!!! I think I can do this with left.  I need to do the above with left as well...
//
//		if (rowwise_types_match && rowwise_heights_match && x_match && rowwise_adjacent_faces) {
//
//			// Merge faces.  On the next iteration, our 'start face' will be
//			// this merged face.
//
//			// Merge (note that we only need to merge the 'next' face
//			// into our 'start face' slot.  Rather than putting all 6 new
//			// faces into the vector, we only need the 3 new ones:
//
//			merged_row_vector.at(merged_vector_size - 6) = vertex.at(i);
//			//merged_row_vector.at(merged_vector_size - 5) = 
//			merged_row_vector.at(merged_vector_size - 4) = vertex.at(i + 2);
//			merged_row_vector.at(merged_vector_size - 3) = vertex.at(i + 3);
//			//merged_row_vector.at(merged_vector_size - 2)
//			//merged_row_vector.at(merged_vector_size - 1)
//
//			//merged_row_vector.at(merged_vector_size - 6) = vertex.at(i);      // Next bottom left
//			////merged_row_vector.at(merged_vector_size - 2) = vertex.at(i + 1);      // Next bottom left
//			//merged_row_vector.at(merged_vector_size - 4) = vertex.at(i + 2);      // Next top left
//			//merged_row_vector.at(merged_vector_size - 3) = vertex.at(i + 2);      // Next top left
//
//		} else {
//
//			// Faces cannot be merged. Push back current face into merged
//			// vector. This becomes the new 'start face'
//			merged_row_vector.push_back(vertex.at(i));
//			merged_row_vector.push_back(vertex.at(i + 1));
//			merged_row_vector.push_back(vertex.at(i + 2));
//			merged_row_vector.push_back(vertex.at(i + 3));
//			merged_row_vector.push_back(vertex.at(i + 4));
//			merged_row_vector.push_back(vertex.at(i + 5));
//		}
//
//	}
//
//	return(merged_row_vector);
//
//	// TODO make sure i can do my face 'type' comparisons correctly...
//	// TODO I think I can...
//
//	// Faces have now been merged per row.  Now we can compare
//	// the merged faces across the y axis.  If x and z are identical for 2
//	// faces, we can merge upward.
//
//	if (merged_row_vector.size() <= 6) {
//		return merged_row_vector;
//	}
//
//	std::vector<VertexAndNormals> merged_y_vector;
//	//merged_y_vector.push_back(merged_row_vector.at(0));
//	//merged_y_vector.push_back(merged_row_vector.at(1));
//	//merged_y_vector.push_back(merged_row_vector.at(2));
//	//merged_y_vector.push_back(merged_row_vector.at(3));
//	//merged_y_vector.push_back(merged_row_vector.at(4));
//	//merged_y_vector.push_back(merged_row_vector.at(5));
//
//	// Keep track of merged faces.  If a face has been merged, we can skip it
//	std::vector<bool> has_been_merged(merged_row_vector.size(), false);
//
//	for (size_t i = 0; i < merged_row_vector.size(); i += 6) {
//
//		// Check if face has been merged.  If it has, we can skip to the next face
//		if (has_been_merged.at(i)) {
//			continue;
//		}
//
//		bool face_can_merge = false;
//		VertexAndNormals next_top_left;
//		VertexAndNormals next_top_right;
//
//		const size_t start_bottom_left_idx = i;
//		const size_t start_bottom_right_idx = i + 1;
//		const size_t start_top_left_idx = i + 2;
//		const size_t start_top_left_idx_second = i + 3;
//		const size_t start_bottom_right_idx_second = i + 4;
//		const size_t start_top_right_idx = i + 5;
//
//		const VertexAndNormals start_bottom_left = merged_row_vector.at(start_bottom_left_idx);
//		const VertexAndNormals start_bottom_right = merged_row_vector.at(start_bottom_right_idx);
//		VertexAndNormals start_top_left = merged_row_vector.at(start_top_left_idx);
//		VertexAndNormals start_top_right = merged_row_vector.at(start_top_right_idx);
//		const signed char start_type = start_bottom_left.m_w;
//
//
//		for (size_t j = i + 6; j < merged_row_vector.size(); j += 6) {
//
//			const size_t next_bottom_left_idx = j;
//			const size_t next_bottom_right_idx = j + 1;
//			const size_t next_top_left_idx = j + 2;
//			const size_t next_top_right_idx = j + 5;
//
//			// Next face (to see if we can merge)
//			const VertexAndNormals next_bottom_left = merged_row_vector.at(next_bottom_left_idx);
//			const VertexAndNormals next_bottom_right = merged_row_vector.at(next_bottom_right_idx);
//			next_top_left = merged_row_vector.at(next_top_left_idx);
//			next_top_right = merged_row_vector.at(next_top_right_idx);
//			const signed char next_type = next_bottom_left.m_w;
//
//			// Merged faces must be the same type.  If the start face and
//			// next face are not the same type, we can continue on to the
//			// next 'next' face
//			if (start_type != next_type) {
//				continue;
//			}
//
//			// Check if start face and next face are adjacent (y).  This is
//			// the top of the start face and bottom of the next face.  If they
//			// are not adjacent (y), move on to the next 'next' face
//			if (start_top_right.m_y > next_bottom_right.m_y) {
//				continue;
//			}
//
//			// If the 'next' block bottom left corner is < than
//			// our bottom left corner, we can continue onto the next
//			// face (remember we are iterating left to right)
//			if (next_bottom_left.m_z < start_bottom_left.m_z) {
//				continue;
//			}
//
//			// If the 'next' block (which is above us at this point),
//			// left corner is greater than the start block left corner,
//			// there are no faces left to merge
//			if (next_bottom_left.m_z > start_bottom_left.m_z) {
//				break;
//			}
//
//			// Check if face has been merged.  If it has, we can skip to the next face
//			if (has_been_merged.at(next_bottom_left_idx)) {
//				continue;
//			}
//
//			// Check is we are at the same depth (x) as our start face.  If
//			// we are not at the same depth, faces cannot be merged and we can
//			// break out of the 'look for faces to merge' loop
//			if (start_bottom_left.m_x != next_bottom_left.m_x) {
//				break;
//			}
//
//
//
//
//			// Check if the start face and next are within one row of each
//			// other if they aren't, it means we are above the necessary row
//			// for merging and can break from the loop
//			if (start_top_right.m_y < next_bottom_right.m_y) {
//				break;
//			}
//
//			// At this point, the start face and next face must be adjacent
//			// in the 'y' direction.  Before merging, we must check if the
//			// both corners are aligned:
//
//
//
//
//
//			// If the next block and current block are aligned then merge:
//
//			// No need to check bottom left 'z' here.  They must be equal to
//			// get to this point
//			// if(start_bottom_left.m_z == next_bottom_left.m_z && start_bottom_right.m_z == next_bottom_right.m_z){
//
//			if (start_bottom_right.m_z == next_bottom_right.m_z) {
//				// Update start variables
//				start_top_left = next_top_left;
//				start_top_right = next_top_right;
//
//				// Flag merge vector (Allows us to skip this face for
//				// consideration of future merges)
//				has_been_merged.at(next_bottom_left_idx) = true;
//				face_can_merge = true;
//			}
//
//		}
//
//		// If we have exited the inner loop, its either because a face was
//		// merged or not.
//		if (face_can_merge) {
//
//			// In the merge loop we update the 'start' top variables.
//			// This allows the inner j loop to continue looking for
//			// more faces after a merge.  However, when we want to
//			// merge, we now need to use the updated 'start'
//			// faces, because they are based on the 'next' faces that they
//			// were able to merge to
//
//			merged_y_vector.push_back(start_bottom_left);
//			merged_y_vector.push_back(start_bottom_right);
//			merged_y_vector.push_back(start_top_left);
//			merged_y_vector.push_back(start_top_left);
//			merged_y_vector.push_back(start_bottom_right);
//			merged_y_vector.push_back(start_top_right);
//
//		} else {
//			merged_y_vector.push_back(start_bottom_left);
//			merged_y_vector.push_back(start_bottom_right);
//			merged_y_vector.push_back(start_top_left);
//			merged_y_vector.push_back(start_top_left);
//			merged_y_vector.push_back(start_bottom_right);
//			merged_y_vector.push_back(start_top_right);
//		}
//
//	}
//
//	return merged_y_vector;
//
//}

std::vector<VertexAndNormals> GreedyMesh::merge_faces(const std::vector<VertexAndNormals>& vertex, const FaceType face_type){
	std::vector<VertexAndNormals> merged_rows = rowwise_merge_faces(vertex, face_type);
	std::vector<VertexAndNormals> merged_across_rows = across_rows_merge_faces(merged_rows, face_type);
	return merged_across_rows;
}
