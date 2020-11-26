#pragma once
#include "../Mesh/OpenGLMesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

namespace OpenGL{

	class OpenGLModelLoader {

	public:
		OpenGLModelLoader(const std::string& path);
		
	private:
		void load();
		void process_node(aiNode* node, const aiScene* scene) const;
		OpenGLMesh process_mesh(aiMesh* mesh, const aiScene* scene);
		
		std::string m_path;
		std::vector<OpenGLMesh> m_mesh_vector;

	};
	
} // namespace OpenGL


