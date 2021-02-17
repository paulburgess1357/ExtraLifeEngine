#include "GreedyMeshExecutor.h"
#include "SortFaces.hpp"
#include "GreedyMesh.h"
#include "GreedyFacePerRowMesh.h"
#include "GreedyRowPerSideMesh.h"
#include <algorithm>

std::vector<VertexAndNormals> GreedyMeshExecutor::run_greedy_mesh(
	const std::vector<VertexAndNormals>& left_faces, 
	const std::vector<VertexAndNormals>& right_faces, 
	const std::vector<VertexAndNormals>& top_faces, 
	const std::vector<VertexAndNormals>& bottom_faces, 
	const std::vector<VertexAndNormals>& front_faces, 
	const std::vector<VertexAndNormals>& back_faces){

	// Mesh each face individually
	const std::vector<VertexAndNormals> left_faces_meshed = mesh_faces(left_faces, FaceType::LEFT);
	const std::vector<VertexAndNormals> right_faces_meshed = mesh_faces(right_faces, FaceType::RIGHT);
	const std::vector<VertexAndNormals> top_faces_meshed = mesh_faces(top_faces, FaceType::TOP);	
	const std::vector<VertexAndNormals> bottom_faces_meshed = mesh_faces(bottom_faces, FaceType::BOTTOM);	
	const std::vector<VertexAndNormals> front_faces_meshed = mesh_faces(front_faces, FaceType::FRONT);
	const std::vector<VertexAndNormals> back_faces_meshed = mesh_faces(back_faces, FaceType::BACK);

	// Combine into single vector:
	std::vector<VertexAndNormals> all_faces_meshed;
	all_faces_meshed.reserve(left_faces_meshed.size() + right_faces_meshed.size() + top_faces_meshed.size() + bottom_faces_meshed.size() + front_faces_meshed.size() + back_faces_meshed.size());
	all_faces_meshed.insert(all_faces_meshed.end(), left_faces_meshed.begin(), left_faces_meshed.end());
	all_faces_meshed.insert(all_faces_meshed.end(), right_faces_meshed.begin(), right_faces_meshed.end());
	all_faces_meshed.insert(all_faces_meshed.end(), top_faces_meshed.begin(), top_faces_meshed.end());
	all_faces_meshed.insert(all_faces_meshed.end(), bottom_faces_meshed.begin(), bottom_faces_meshed.end());
	all_faces_meshed.insert(all_faces_meshed.end(), front_faces_meshed.begin(), front_faces_meshed.end());
	all_faces_meshed.insert(all_faces_meshed.end(), back_faces_meshed.begin(), back_faces_meshed.end());

	return all_faces_meshed;
}

std::vector<VertexAndNormals> GreedyMeshExecutor::mesh_faces(const std::vector<VertexAndNormals>& faces, const FaceType face_type) {
	// Sort (Top/Bottom and Front/Back must be sorted prior to merge)
	const std::vector<VertexAndNormals> sorted_faces = sort_faces(faces, face_type);		
	return GreedyRowPerSideMesh::merge_rows(GreedyFacePerRowMesh::merge_all_faces(sorted_faces, face_type), face_type);
}

std::vector<VertexAndNormals> GreedyMeshExecutor::sort_faces(const std::vector<VertexAndNormals>& faces, FaceType face_type){

	// Left/Right faces do not have to be sorted.  This is because faces are generated
	// along the Z axis (so they are already sorted)
	
	switch (face_type) {

		case FaceType::FRONT: {
			std::vector<Face> face_vector = GreedyMesh::vertex_vector_to_face_vector(faces);
			std::sort(face_vector.begin(), face_vector.end(), sort_front_back_faces());
			return GreedyMesh::face_vertor_to_vertex(face_vector);
		}

		case FaceType::BACK: {
			std::vector<Face> face_vector = GreedyMesh::vertex_vector_to_face_vector(faces);
			std::sort(face_vector.begin(), face_vector.end(), sort_front_back_faces());
			return GreedyMesh::face_vertor_to_vertex(face_vector);
		}

		case FaceType::TOP: {
			std::vector<Face> face_vector = GreedyMesh::vertex_vector_to_face_vector(faces);
			std::sort(face_vector.begin(), face_vector.end(), sort_top_bottom_faces());
			return GreedyMesh::face_vertor_to_vertex(face_vector);
		}

		case FaceType::BOTTOM: {
			std::vector<Face> face_vector = GreedyMesh::vertex_vector_to_face_vector(faces);
			std::sort(face_vector.begin(), face_vector.end(), sort_top_bottom_faces());
			return GreedyMesh::face_vertor_to_vertex(face_vector);
		}

		default: {
			return faces;
		}
	}
}
