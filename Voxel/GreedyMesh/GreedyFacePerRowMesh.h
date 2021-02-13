#pragma once
#include "GreedyMesh.h"
#include "../Neutral/VertexAndNormals.h"
#include "../Neutral/FaceType.h"
#include "../Neutral/Face.h"
#include <vector>

class GreedyFacePerRowMesh : public GreedyMesh {

	// Merge faces per for (.e.g left to right or right to left)
	// TODO change name.  Rows are merged for left/right
	// TODO columns are merged for front/back
	
public:
	static std::vector<VertexAndNormals> merge_all_faces(const std::vector<VertexAndNormals>& vertex, const FaceType face_type);

private:
	static void merge_face(std::vector<VertexAndNormals>& merged_vector, const Face& next_face, const FaceType face_type, const size_t start_idx);
	static bool is_mergeable(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool is_adjacent(const Face& start_face, const Face& next_face, const FaceType face_type);
};

