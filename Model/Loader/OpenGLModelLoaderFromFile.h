#pragma once
#include "../Mesh/OpenGLMesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <string>

namespace OpenGL{

	class OpenGLModelLoaderFromFile {

	public:
		OpenGLModelLoaderFromFile(const std::string& path);
		std::vector<OpenGLMesh> load();
		void set_shader_program(const std::shared_ptr<IShaderProgram>& shader_program);
		
	private:		
		void process_node(aiNode* node, const aiScene* scene);		
		OpenGLMesh process_mesh(aiMesh* mesh, const aiScene* scene) const;
		
		std::string m_path;
		std::string m_directory;
		std::vector<OpenGLMesh> m_mesh_vector;
		std::shared_ptr<IShaderProgram> m_shader_program;

	};
	
} // namespace OpenGL


