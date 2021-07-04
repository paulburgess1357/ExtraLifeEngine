#pragma once
#include "../Mesh/OpenGLMesh.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <string>

namespace OpenGL{

	class OpenGLModelLoaderFromFile {

	public:
		OpenGLModelLoaderFromFile(const std::string& path, IShaderProgram& shader_program, const bool assimp_flip_uvs);
		std::vector<OpenGLMesh> load();
		
	private:		
		void process_node(aiNode* node, const aiScene* scene);		
		OpenGLMesh process_mesh(aiMesh* mesh, const aiScene* scene) const;
		
		std::string m_path;
		bool m_assimp_flip_uv;
		std::string m_directory;
		std::vector<OpenGLMesh> m_mesh_vector;
		IShaderProgram& m_shader_program;
	};
	
} // namespace OpenGL


