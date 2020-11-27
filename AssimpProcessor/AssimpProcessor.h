#pragma once
#include "../Model/Vertex.h"
#include <vector>
#include <assimp/scene.h>

class AssimpProcessor{
	
public:
	static std::vector<Vertex> process_verticies(const aiMesh* mesh);
	static std::vector<unsigned int> process_faces(const aiMesh* mesh);
	
private:
	static void process_vertex_positions(Vertex& vertex, const aiVector3D assimp_vertex);
	static void process_vertex_normals(Vertex& vertex, const aiVector3D assimp_normals);
	static void process_texture_coords(Vertex& vertex, const aiVector3D assimp_texture_coords);
	static void process_tangents(Vertex& vertex, const aiVector3D assimp_tangents);
	static void process_bittangents(Vertex& vertex, const aiVector3D assimp_bittangents);
};

