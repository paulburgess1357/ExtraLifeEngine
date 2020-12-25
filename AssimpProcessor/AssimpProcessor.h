#pragma once
#include "../Model/Vertex.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <vector>
#include <string>

class AssimpProcessor{
	
public:
	const aiScene* create_scene_loader(const std::string& full_model_path, const bool assimp_flip_uvs);
	static std::vector<Vertex> process_verticies(const aiMesh* mesh);
	static std::vector<unsigned int> process_faces(const aiMesh* mesh);
	
private:
	static void check_assimp_importer(const Assimp::Importer& importer, const aiScene* scene);
	static void process_vertex_positions(Vertex& vertex, const aiVector3D assimp_vertex);
	static void process_vertex_normals(Vertex& vertex, const aiVector3D assimp_normals);
	static void process_texture_coords(Vertex& vertex, const aiVector3D assimp_texture_coords);
	static void process_tangents(Vertex& vertex, const aiVector3D assimp_tangents);
	static void process_bittangents(Vertex& vertex, const aiVector3D assimp_bittangents);

	Assimp::Importer m_assimp_importer;
};

