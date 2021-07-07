#pragma once
#include "../Neutral/VertexAndNormals.h"
#include "../Neutral/FaceType.h"
#include <vector>

class GreedyMeshExecutor{

public:
	static std::vector<VertexAndNormals> run_greedy_mesh(
		const std::vector<VertexAndNormals>& left_faces,
		const std::vector<VertexAndNormals>& right_faces,
		const std::vector<VertexAndNormals>& top_faces,
		const std::vector<VertexAndNormals>& bottom_faces,
		const std::vector<VertexAndNormals>& front_faces,
		const std::vector<VertexAndNormals>& back_faces
	);
	
private:
	static std::vector<VertexAndNormals> mesh_faces(const std::vector<VertexAndNormals>& faces, FaceType face_type);
	static std::vector<VertexAndNormals> sort_faces(const std::vector<VertexAndNormals>& faces, FaceType face_type);
	
};
