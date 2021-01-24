#pragma once
#include "../Neutral/VertexAndNormals.h"
#include "../Neutral/FaceType.h"
#include "../Neutral/Face.h"
#include <vector>

class GreedyMesh{

public:
	static std::vector<VertexAndNormals> merge_faces(const std::vector<VertexAndNormals>& vertex, const FaceType face_type);
	
	static std::vector<VertexAndNormals> rowwise_merge_faces(const std::vector<VertexAndNormals>& vertex, const FaceType face_type);
	static std::vector<VertexAndNormals> across_rows_merge_faces(const std::vector<VertexAndNormals>& merged_row_vector, const FaceType face_type);
private:

	static void rowwise_merge(std::vector<VertexAndNormals>& merged_vector, const Face& next_face, const FaceType face_type, const size_t start_idx);
	static bool rowwise_is_mergeable(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool rowwise_adjacent_faces(const Face& start_face, const Face& next_face, const FaceType face_type);

	static bool top_start_and_bottom_next_corner_same_height(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool block_too_early(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool past_merge_location(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool depths_match(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool past_merge_row(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool corners_aligned(const Face& start_face, const Face& next_face, const FaceType face_type);

	
	static Face get_face(const std::vector<VertexAndNormals>& vertex, const size_t start_idx);
	static void pushback_face(std::vector<VertexAndNormals>& fill_vector, const Face& face);

	static bool types_match(const Face& start_face, const Face& next_face);

	//TODO change this?  I can check width (bottom corners) or height(top corners), or all 4?
	// TODO need to make sure the definition I choose works with existing checks.
	// TODO likely should do width versions (x_width_match) and height versions (x_height_match)
	static bool y_match(const Face& start_face, const Face& next_face);
	static bool x_match(const Face& start_face, const Face& next_face);


	
	static bool z_width_match(const Face& start_face, const Face& next_face);	
};

