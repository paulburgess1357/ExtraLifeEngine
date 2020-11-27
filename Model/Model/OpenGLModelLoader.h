#pragma once
#include "../Mesh/OpenGLMesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <string>

namespace OpenGL{

	class OpenGLModelLoader {

	public:
		OpenGLModelLoader(const std::string& path);
		
	private:
		void load();
		void process_node(aiNode* node, const aiScene* scene);
		OpenGLMesh process_mesh(aiMesh* mesh, const aiScene* scene) const;
		//static std::vector<Vertex> process_vertices(const aiMesh* mesh);

		



		

		static void check_assimp_importer(const Assimp::Importer& importer, const aiScene* scene);
		
		std::string m_path;
		std::string m_directory;
		std::vector<OpenGLMesh> m_mesh_vector;

	};
	
} // namespace OpenGL


