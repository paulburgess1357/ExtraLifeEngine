#include "GreedyMesh.h"

Face GreedyMesh::get_face(const std::vector<VertexAndNormals>& vertex, const size_t start_idx) {
	return Face{
		vertex.at(start_idx),     // Bottom Left
		vertex.at(start_idx + 1), // Bottom Right
		vertex.at(start_idx + 2), // Top left
		vertex.at(start_idx + 5)  // Top Right
	};
}

void GreedyMesh::pushback_face(std::vector<VertexAndNormals>& fill_vector, const Face& face) {
	fill_vector.push_back(face.get_bottom_left());
	fill_vector.push_back(face.get_bottom_right());
	fill_vector.push_back(face.get_top_left());
	fill_vector.push_back(face.get_top_left());
	fill_vector.push_back(face.get_bottom_right());
	fill_vector.push_back(face.get_top_right());
}

bool GreedyMesh::types_match(const Face& start_face, const Face& next_face) {
	return start_face.get_type() == next_face.get_type();
}

bool GreedyMesh::heights_match(const Face& start_face, const Face& next_face, const FaceType face_type) {
	bool height_match = false;

	switch (face_type) {

		case FaceType::LEFT: {
			height_match = start_face.get_bottom_left().m_y == next_face.get_bottom_left().m_y && start_face.get_top_left().m_y == next_face.get_top_left().m_y;
			break;
		}

		case FaceType::RIGHT:{
			height_match = start_face.get_bottom_left().m_y == next_face.get_bottom_left().m_y && start_face.get_top_left().m_y == next_face.get_top_left().m_y;
			break;
		}

		default: {
			break;
		}
	}

	return height_match;
}

bool GreedyMesh::depths_match(const Face& start_face, const Face& next_face, const FaceType face_type) {

	// Since no merging is done across depths (i.e. across 'slices' of the chunk),
	// only one value of the depth is necessary to check.  If they are not equal,
	// it means we are on different slices.
	
	bool depth_match = false;

	switch (face_type) {
		case FaceType::LEFT: {
			depth_match = start_face.get_bottom_left().m_x == next_face.get_bottom_left().m_x;
			break;
		}

		case FaceType::RIGHT:{
			depth_match = start_face.get_bottom_left().m_x == next_face.get_bottom_left().m_x;
			break;
		}

		default: {
			break;
		}
	}

	return depth_match;
}

bool GreedyMesh::widths_match(const Face& start_face, const Face& next_face, const FaceType face_type) {
	bool widths_match = false;

	switch (face_type) {
		case FaceType::LEFT: {
			widths_match = start_face.get_bottom_left().m_z == next_face.get_bottom_left().m_z && start_face.get_bottom_right().m_z == next_face.get_bottom_right().m_z;
			break;
		}

		case FaceType::RIGHT:{
			widths_match = start_face.get_bottom_left().m_z == next_face.get_bottom_left().m_z && start_face.get_bottom_right().m_z == next_face.get_bottom_right().m_z;
			break;
		}

		default: {
			break;
		}
	}

	return widths_match;
}