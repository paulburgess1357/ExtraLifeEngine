#include "AssimpProcessor.h"
#include "../Utility/FatalError.h"
#include <assimp/postprocess.h>

#include "../Utility/Print.h"

const aiScene* AssimpProcessor::create_scene_loader(const std::string& full_model_path){

	const aiScene* scene = m_assimp_importer.ReadFile(full_model_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes); //aiProcess_FlipUVs

	check_assimp_importer(m_assimp_importer, scene);
	return scene;
	
}

void AssimpProcessor::check_assimp_importer(const Assimp::Importer& importer, const aiScene* scene) {
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		FatalError::fatal_error("Assimp ReadFile Error: " + std::string(importer.GetErrorString()));
	}
}


std::vector<Vertex> AssimpProcessor::process_verticies(const aiMesh* mesh){

	std::vector<Vertex> mesh_verticies;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

		Vertex current_vertex;

		if (mesh->HasPositions()) {
			process_vertex_positions(current_vertex, mesh->mVertices[i]);
		}

		if (mesh->HasNormals()) {
			process_vertex_normals(current_vertex, mesh->mNormals[i]);
		}

		if (mesh->HasTextureCoords(0)) {
			process_texture_coords(current_vertex, mesh->mTextureCoords[0][i]);
		}

		if (mesh->HasTangentsAndBitangents()) {
			process_tangents(current_vertex, mesh->mTangents[i]);
			process_bittangents(current_vertex, mesh->mBitangents[i]);
		}

		mesh_verticies.push_back(current_vertex);

	}

	return mesh_verticies;
	
}

void AssimpProcessor::process_vertex_positions(Vertex& vertex, const aiVector3D assimp_vertex) {
	vertex.m_position.x = assimp_vertex.x;
	vertex.m_position.y = assimp_vertex.y;
	vertex.m_position.z = assimp_vertex.z;
}

void AssimpProcessor::process_vertex_normals(Vertex& vertex, const aiVector3D assimp_normals) {
	vertex.m_normals.x = assimp_normals.x;
	vertex.m_normals.y = assimp_normals.y;
	vertex.m_normals.z = assimp_normals.z;
}

void AssimpProcessor::process_texture_coords(Vertex& vertex, const aiVector3D assimp_texture_coords) {

	// Assimp contains a texture coordinate array with 2 dimensions.  We
	// only require textures on the first row (so index = 0)

	vertex.m_tex_coords.x = assimp_texture_coords.x;
	vertex.m_tex_coords.y = assimp_texture_coords.y;
}

void AssimpProcessor::process_tangents(Vertex& vertex, const aiVector3D assimp_tangents) {
	vertex.m_tangent.x = assimp_tangents.x;
	vertex.m_tangent.y = assimp_tangents.y;
	vertex.m_tangent.z = assimp_tangents.z;
}

void AssimpProcessor::process_bittangents(Vertex& vertex, const aiVector3D assimp_bittangents) {
	vertex.m_bitangent.x = assimp_bittangents.x;
	vertex.m_bitangent.y = assimp_bittangents.y;
	vertex.m_bitangent.z = assimp_bittangents.z;
}

std::vector<unsigned> AssimpProcessor::process_faces(const aiMesh* mesh){

	// Each face contains a single primitive (in our case its a triangle).
	// A face contains the indicies of the verticies we need to draw.
	// We iterate over all the faces and store all the face indicies

	std::vector<unsigned int> vertex_indicies;

	for(unsigned int i = 0; i < mesh->mNumFaces; i++){

		const aiFace current_face = mesh->mFaces[i];

		for(unsigned int j = 0; j < current_face.mNumIndices; j++){
			const unsigned int current_index = current_face.mIndices[j];
			vertex_indicies.push_back(current_index);			
		}				
	}

	return vertex_indicies;
}