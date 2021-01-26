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

		default: {
			break;
		}
	}

	return widths_match;
}















// TODO does widths match replace this?
//bool GreedyMesh::corners_aligned(const Face& start_face, const Face& next_face, const FaceType face_type){
//	bool corners_aligned = false;
//
//	switch (face_type) {
//		case FaceType::LEFT: {
//			corners_aligned = z_width_match(start_face, next_face);
//			//corners_aligned = start_face.get_bottom_right().m_z == next_face.get_bottom_right().m_z;
//			break;
//		}
//
//		default: {
//			break;
//		}
//	}
//
//	return corners_aligned;
//}

//bool GreedyMesh::z_width_match(const Face& start_face, const Face& next_face) {
//	return start_face.get_bottom_left().m_z == next_face.get_bottom_left().m_z &&
//		   start_face.get_bottom_right().m_z == next_face.get_bottom_right().m_z;
//}

//bool GreedyMesh::y_match(const Face& start_face, const Face& next_face){
//	return start_face.get_bottom_left().m_y == next_face.get_bottom_left().m_y && 
//		   start_face.get_top_left().m_y == next_face.get_top_left().m_y;
//}

//bool GreedyMesh::x_match(const Face& start_face, const Face& next_face){
//	return start_face.get_bottom_left().m_x == next_face.get_bottom_left().m_x &&
//		start_face.get_top_left().m_x == next_face.get_top_left().m_x;
//}






//bool GreedyMesh::top_start_and_bottom_next_corner_too_far_apart(const Face& start_face, const Face& next_face, const FaceType face_type){
//	bool too_far_apart = false;
//
//	switch (face_type) {
//		case FaceType::LEFT: {
//			too_far_apart = start_face.get_top_right().m_y < next_face.get_bottom_right().m_y;
//
//
//			break;
//		}
//
//		default: {
//			break;
//		}
//	}
//
//	return too_far_apart;
//}



//std::vector<VertexAndNormals> GreedyMesh::merge_faces(const std::vector<VertexAndNormals>& vertex, const FaceType face_type){
//	std::vector<VertexAndNormals> merged_rows = rowwise_merge_faces(vertex, face_type);
//	std::vector<VertexAndNormals> merged_across_rows = across_rows_merge_faces(merged_rows, face_type);
//	return merged_across_rows;
//}
