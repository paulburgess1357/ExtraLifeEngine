#include "GreedyFacePerRowMesh.h"

std::vector<VertexAndNormals> GreedyFacePerRowMesh::merge_all_faces(const std::vector<VertexAndNormals>& vertex, const FaceType face_type) {

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
		if (is_mergeable(start_face, next_face, face_type)) {
			merge_face(merged_row_vector, next_face, face_type);
		} else {
			pushback_face(merged_row_vector, next_face);
		}

	}

	return(merged_row_vector);
}

bool GreedyFacePerRowMesh::is_mergeable(const Face& start_face, const Face& next_face, const FaceType face_type) {
	return types_match(start_face, next_face) && heights_match(start_face, next_face, face_type) &&
		depths_match(start_face, next_face, face_type) && is_adjacent(start_face, next_face, face_type);
}

void GreedyFacePerRowMesh::merge_face(std::vector<VertexAndNormals>& merged_vector, const Face& next_face, const FaceType face_type) {

	// Merge (note that we only need to merge the 'next' face
	// into our 'start face' slot.  Rather than putting all 6 new
	// faces into the vector, we only need the 3 new ones:

	// bottom left: merged_vector_size - 6
	// bottom right: merged_vector_size - 5
	// top left: merged_vector_size - 4
	// top left: merged_vector_size - 3
	// bottom right: merged_vector_size - 2
	// top right: merged_vector_size - 1
	
	const size_t merged_vector_size = merged_vector.size();

	switch(face_type){
		case FaceType::LEFT:
		case FaceType::FRONT:
		case FaceType::TOP:
		case FaceType::BOTTOM:
			merged_vector.at(merged_vector_size - 5) = next_face.get_bottom_right();
			merged_vector.at(merged_vector_size - 2) = next_face.get_bottom_right();
			merged_vector.at(merged_vector_size - 1) = next_face.get_top_right();
			break;
		case FaceType::RIGHT:
		case FaceType::BACK:
			merged_vector.at(merged_vector_size - 6) = next_face.get_bottom_left();
			merged_vector.at(merged_vector_size - 4) = next_face.get_top_left();
			merged_vector.at(merged_vector_size - 3) = next_face.get_top_left();
			break;
	}
	
}

bool GreedyFacePerRowMesh::is_adjacent(const Face& start_face, const Face& next_face, const FaceType face_type) {

	bool adjacent = false;

	switch(face_type){
		case FaceType::LEFT:
			adjacent = start_face.get_bottom_right().m_z == next_face.get_bottom_left().m_z;
			break;
		case FaceType::RIGHT:
			adjacent = start_face.get_bottom_left().m_z == next_face.get_bottom_right().m_z;
			break;
		case FaceType::TOP:
		case FaceType::BOTTOM:
		case FaceType::FRONT:
			adjacent = start_face.get_bottom_right().m_x == next_face.get_bottom_left().m_x;
			break;
		case FaceType::BACK:
			adjacent = start_face.get_bottom_left().m_x == next_face.get_bottom_right().m_x;
			break;

		default:
			break;
	}

	return adjacent;
}