#pragma once
#include "AssimpProcessor.h"
#include "../ResourceManagement/TextureResource.h"
#include "../Model/Mesh/OpenGLMesh.h"
#include "../Environment/OpenGL/Texture/OpenGLTextureHandler.h"
#include <assimp/scene.h>

namespace OpenGL{

	class OpenGLAssimpProcessor : public AssimpProcessor {
		
	public:		
		static void load_all_materials(const aiMesh* assimp_mesh, const aiScene* scene, const std::string& directory, OpenGLMesh& mesh, TextureResource& texture_resource);

	private:
		static void load_material(const aiMaterial* material, const aiTextureType, const std::string& directory, OpenGLMesh& mesh, TextureResource& texture_resource);
		static void load_material_into_mesh(const std::string& material_name, const aiTextureType texture_type, OpenGLMesh& mesh, const ITexture& mesh_texture);
		static std::string update_material_path(const std::string& material_path, const std::string& directory);
	};
	
} // namespace OpenGL



