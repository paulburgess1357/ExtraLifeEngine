#pragma once
#include "../Neutral/VertexAndNormals.h"
#include "../Neutral/FaceType.h"
#include "../Neutral/Face.h"
#include <vector>

class GreedyMesh{
	
public:
	static std::vector<Face> vertex_vector_to_face_vector(const std::vector<VertexAndNormals>& vertex);
	static std::vector<VertexAndNormals> face_vector_to_vertex(const std::vector<Face>& faces);
	
protected:
	static Face get_face(const std::vector<VertexAndNormals>& vertex, const size_t start_idx);
	static void pushback_face(std::vector<VertexAndNormals>& fill_vector, const Face& face);
	
	static bool types_match(const Face& start_face, const Face& next_face);
	static bool depths_match(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool heights_match(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool widths_match(const Face& start_face, const Face& next_face, const FaceType face_type);						
};