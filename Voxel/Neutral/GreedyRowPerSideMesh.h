#pragma once
#pragma once
#include "../Neutral/GreedyMesh.h"
#include "../Neutral/VertexAndNormals.h"
#include "../Neutral/FaceType.h"
#include "../Neutral/Face.h"
#include <vector>

class GreedyRowPerSideMesh : public GreedyMesh{
	
public:
	static std::vector<VertexAndNormals> merge_rows(const std::vector<VertexAndNormals>& merged_row_vector, const FaceType face_type);
	
private:
	static bool correct_row_to_merge(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool block_too_early(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool past_merge_location(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool past_merge_row(const Face& start_face, const Face& next_face, const FaceType face_type);	
};

