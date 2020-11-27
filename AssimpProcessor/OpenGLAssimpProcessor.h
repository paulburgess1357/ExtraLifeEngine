#pragma once
#include "AssimpProcessor.h"
#include "../Environment/OpenGL/Texture/OpenGLTextureHandler.h"
#include <assimp/scene.h>

namespace OpenGL{

	class OpenGLAssimpProcessor : public AssimpProcessor {
		
	public:		
		OpenGLTextureHandler load_material(const aiMaterial* material, const aiTextureType, const std::string& directory);

	private:				
		void load_material_into_handler(const aiTextureType texture_type, const std::string& material_name);		
		static std::string update_material_path(const std::string& material_path, const std::string& directory);

		OpenGLTextureHandler m_texture_handler;
	};
	
} // namespace OpenGL



