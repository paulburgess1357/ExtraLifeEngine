#include "GreedyRowPerSideMesh.h"

std::vector<VertexAndNormals> GreedyRowPerSideMesh::merge_rows(const std::vector<VertexAndNormals>& merged_row_vector, const FaceType face_type) {

	// Faces have now been merged per row.  Now we can compare
	// the merged faces across the 'height' axis.  Note that the term 'height'
	// is not always 'y', but rather its relative to the face.

	if (merged_row_vector.size() <= 6) {
		return merged_row_vector;
	}
	
	std::vector<VertexAndNormals> merged_y_vector;
	std::vector<bool> has_been_merged(merged_row_vector.size(), false);
	
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
			// other. If they aren't, it means we are above the necessary row
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

				merge_rows(start_face, next_face, face_type);

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

	switch(face_type){
		case FaceType::LEFT:
		case FaceType::RIGHT:
		case FaceType::FRONT:
		case FaceType::BACK:
			past_merge_row = start_face.get_top_right().m_y < next_face.get_bottom_right().m_y;
			break;
		case FaceType::TOP:
			past_merge_row = start_face.get_bottom_right().m_z < next_face.get_top_right().m_z;
			break;
		case FaceType::BOTTOM:
			past_merge_row = start_face.get_top_right().m_z < next_face.get_bottom_right().m_z;
			break;
		default:
			break;
		
	}	

	return past_merge_row;
}

bool GreedyRowPerSideMesh::correct_row_to_merge(const Face& start_face, const Face& next_face, const FaceType face_type) {
	bool same_height = false;

	switch (face_type) {
		case FaceType::LEFT:
		case FaceType::RIGHT:
		case FaceType::FRONT:
		case FaceType::BACK:
			same_height = start_face.get_top_right().m_y == next_face.get_bottom_right().m_y;
			break;
		case FaceType::TOP:
			same_height = start_face.get_bottom_right().m_z == next_face.get_top_right().m_z;
			break;
		case FaceType::BOTTOM:
			same_height = start_face.get_top_right().m_z == next_face.get_bottom_right().m_z;
			break;
		default:
			break;
	}

	return same_height;
}

bool GreedyRowPerSideMesh::block_too_early(const Face& start_face, const Face& next_face, const FaceType face_type) {
	bool too_early = false;

	switch (face_type) {
		case FaceType::LEFT:
		case FaceType::RIGHT:
			too_early = next_face.get_bottom_left().m_z < start_face.get_bottom_left().m_z;
			break;
		case FaceType::FRONT:
		case FaceType::BACK:
		case FaceType::TOP:
		case FaceType::BOTTOM:
			too_early = next_face.get_bottom_left().m_x < start_face.get_bottom_left().m_x;
			break;
		default:
			break;
	}

	return too_early;
}

bool GreedyRowPerSideMesh::past_merge_location(const Face& start_face, const Face& next_face, const FaceType face_type) {
	bool past_merge_location = false;

	switch (face_type) {
		case FaceType::LEFT:
		case FaceType::RIGHT:
			past_merge_location = next_face.get_bottom_left().m_z > start_face.get_bottom_left().m_z;
			break;
		case FaceType::FRONT:
		case FaceType::BACK:
		case FaceType::TOP:
		case FaceType::BOTTOM:
			past_merge_location = next_face.get_bottom_left().m_x > start_face.get_bottom_left().m_x;
			break;
		default:
			break;
	}

	return past_merge_location;
}

void GreedyRowPerSideMesh::merge_rows(Face& start_face, const Face& next_face, const FaceType face_type) {

	switch (face_type) {
		case FaceType::LEFT:
		case FaceType::RIGHT:
		case FaceType::FRONT:
		case FaceType::BACK:
		case FaceType::BOTTOM:
			start_face.set_top_left(next_face.get_top_left());
			start_face.set_top_right(next_face.get_top_right());
			break;
		case FaceType::TOP:
			start_face.set_bottom_left(next_face.get_bottom_left());
			start_face.set_bottom_right(next_face.get_bottom_right());
			break;
		default:
			break;
	}
}