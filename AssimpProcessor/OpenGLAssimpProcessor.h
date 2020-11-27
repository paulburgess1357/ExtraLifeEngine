#pragma once
#include "AssimpProcessor.h"
#include "../Environment/OpenGL/Texture/OpenGLTextureHandler.h"
#include <assimp/scene.h>

namespace OpenGL{

	class OpenGLAssimpProcessor : public AssimpProcessor {
		
	public:		
		static OpenGLTextureHandler load_all_materials(const aiMesh* mesh, const aiScene* scene, const std::string& directory, const std::shared_ptr<IShaderProgram>& shader_program);

	private:
		static void load_material(OpenGLTextureHandler& texture_handler, const aiMaterial* material, const aiTextureType, const std::string& directory);
		static void load_material_into_handler(OpenGLTextureHandler& texture_handler, const std::string& material_name, const aiTextureType texture_type);
		static std::string update_material_path(const std::string& material_path, const std::string& directory);
	};
	
} // namespace OpenGL



