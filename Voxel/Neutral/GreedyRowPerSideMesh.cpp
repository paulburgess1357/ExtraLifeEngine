#include "GreedyRowPerSideMesh.h"

std::vector<VertexAndNormals> GreedyRowPerSideMesh::merge_rows(const std::vector<VertexAndNormals>& merged_row_vector, const FaceType face_type) {

	// Faces have now been merged per row.  Now we can compare
	// the merged faces across the 'height' axis.  Note that the term 'height'
	// is not always 'y', but rather its relative to the face.

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

		Face start_face = get_face(merged_row_vector, i);
		Face next_face;

		for (size_t j = i + 6; j < merged_row_vector.size(); j += 6) {

			// Next face (to see if we can merge)
			next_face = get_face(merged_row_vector, j);

			// Check if the start face and next are within one row of each
			// other if they aren't, it means we are above the necessary row
			// for merging and can break from the loop
			if (past_merge_row(start_face, next_face, face_type)) {
				break;
			}

			// Check if next face and start face are the same type:
			if (!types_match(start_face, next_face)) {
				continue;
			}

			// Check if the next face is on the correct row to merge:
			if (!correct_row_to_merge(start_face, next_face, face_type)) {
				continue;
			}

			// Check if the next block corner is < our start block corner.  If
			// it is, we are too early to merge.
			if (block_too_early(start_face, next_face, face_type)) {
				continue;
			}

			// Check if the next block corner is > our start block corner.  If
			// it is, we are past the possible merge location.
			if (past_merge_location(start_face, next_face, face_type)) {
				break;
			}

			// Check if face has been merged.  If it has, there is no need to
			// examine it further.
			if (has_been_merged.at(j)) {
				continue;
			}

			// Check is we are at the same depth (x) as our start face.  If we
			// are at different depths, we can break from the inner loop.
			if (!depths_match(start_face, next_face, face_type)) {
				break;
			}

			// At this point, the start face and next face must be adjacent
			// in the 'height' direction (depending on the face, this is not
			// alway 'y', but rather its relative to the face location).
			// Before merging, we must check if both corners are aligned.

			if (widths_match(start_face, next_face, face_type)) {

				// Merge next face into start face

				// In the merge loop we update the 'start' face if a merge is
				// possible.  This makes it possible for the inner j loop to
				// continue iterating as it merges (e.g. merging multiple rows
				// for a single block - think stack of 4 individual blocks into
				// a single block)

				start_face.set_top_left(next_face.get_top_left());
				start_face.set_top_right(next_face.get_top_right());

				// Flag merge vector
				has_been_merged.at(j) = true;
			}

		}

		// Push back the start face (which may or may not have been merged)
		pushback_face(merged_y_vector, start_face);
	}

	return merged_y_vector;

}

bool GreedyRowPerSideMesh::past_merge_row(const Face& start_face, const Face& next_face, const FaceType face_type) {
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

bool GreedyRowPerSideMesh::block_too_early(const Face& start_face, const Face& next_face, const FaceType face_type) {
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

bool GreedyRowPerSideMesh::past_merge_location(const Face& start_face, const Face& next_face, const FaceType face_type) {
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

bool GreedyRowPerSideMesh::correct_row_to_merge(const Face& start_face, const Face& next_face, const FaceType face_type) {
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