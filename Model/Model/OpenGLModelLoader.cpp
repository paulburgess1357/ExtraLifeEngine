#include "OpenGLModelLoader.h"
#include "../Vertex.h"
#include "../AssimpProcessor.h"
#include "../../Utility/FatalError.h"
#include "../../Utility/FileHandler.h"
#include <assimp/postprocess.h>

OpenGL::OpenGLModelLoader::OpenGLModelLoader(const std::string& path)
	:m_path{ path },
	 m_directory{ FileHandler::get_file_directory(m_path) }{
	
}

void OpenGL::OpenGLModelLoader::load(){

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(m_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);

	check_assimp_importer(importer, scene);
	process_node(scene->mRootNode, scene);
	
	
	
}

void OpenGL::OpenGLModelLoader::check_assimp_importer(const Assimp::Importer& importer, const aiScene* scene){

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		FatalError::fatal_error("Assimp ReadFile Error: " + std::string(importer.GetErrorString()));
	}
	
}



void OpenGL::OpenGLModelLoader::process_node(aiNode* node, const aiScene* scene) {

	// The node contains n number of mesh indicies.  The mesh data is stored
	// in the aiScene object.  The mesh data is retrieved using the indicies
	// in the node.

	// After mesh data is pulled from the scene object, it is processed via
	// process_mesh.  This function converts aiMesh data into our own mesh
	// class

	// Nodes can have any number of child nodes.  a child node is processed
	// the same way as a root node.

	// Process all of the nodes meshes
	for(unsigned int i = 0; i < node->mNumMeshes; i++){
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		OpenGLMesh opengl_mesh = process_mesh(mesh, scene);
		m_mesh_vector.push_back(opengl_mesh);
	}

	// Process all of the nodes children's meshes
	for(unsigned int i=0; i < node->mNumChildren; i++){
		process_node(node->mChildren[i], scene);
	}
	
	
	
}

OpenGL::OpenGLMesh OpenGL::OpenGLModelLoader::process_mesh(aiMesh* mesh, const aiScene* scene) const{

	const std::vector<Vertex> mesh_vertices{ AssimpProcessor::process_verticies(mesh) };
	const std::vector<unsigned int> mesh_indicies{ AssimpProcessor::process_faces(mesh) };
	
	
}




