#include "OpenGLModelLoaderFromFile.h"
#include "../Vertex.h"
#include "../../AssimpProcessor/OpenGLAssimpProcessor.h"
#include "StringUtilities/FilePath/FilePath.hpp"

OpenGL::OpenGLModelLoaderFromFile::OpenGLModelLoaderFromFile(const std::string& path, IShaderProgram& shader_program, TextureResource& texture_resource, const bool assimp_flip_uvs)
	:m_path{ path },
     m_assimp_flip_uv{ assimp_flip_uvs },
     m_directory{ StringUtil::FilePath::get_directory(m_path)},
	 m_shader_program{ shader_program },
	 m_texture_resource{ texture_resource }{
	
}

std::vector<OpenGL::OpenGLMesh> OpenGL::OpenGLModelLoaderFromFile::load(){

	AssimpProcessor assimp_processor;
	const aiScene* scene = assimp_processor.create_scene_loader(m_path, m_assimp_flip_uv);
	
	process_node(scene->mRootNode, scene);

	return m_mesh_vector;
			
}

void OpenGL::OpenGLModelLoaderFromFile::process_node(aiNode* node, const aiScene* scene) {

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

OpenGL::OpenGLMesh OpenGL::OpenGLModelLoaderFromFile::process_mesh(aiMesh* mesh, const aiScene* scene) const {

	const std::vector<Vertex> mesh_vertices{ AssimpProcessor::process_verticies(mesh) };
	const std::vector<unsigned int> mesh_indicies{ AssimpProcessor::process_faces(mesh) };

	OpenGLMesh opengl_mesh{ mesh_vertices, mesh_indicies, m_shader_program};
	OpenGLAssimpProcessor::load_all_materials(mesh, scene, m_directory, opengl_mesh, m_texture_resource); // requires texture resource
		
	return opengl_mesh;	
}
