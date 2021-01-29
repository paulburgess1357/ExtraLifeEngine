#pragma once
#include "../Neutral/VertexAndNormals.h"
#include "../Neutral/FaceType.h"
#include "../Neutral/Face.h"
#include <vector>

class GreedyMesh{

protected:
	static Face get_face(const std::vector<VertexAndNormals>& vertex, const size_t start_idx);
	static void pushback_face(std::vector<VertexAndNormals>& fill_vector, const Face& face);
	
	static bool types_match(const Face& start_face, const Face& next_face);
	static bool depths_match(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool heights_match(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool widths_match(const Face& start_face, const Face& next_face, const FaceType face_type);	
					
};

