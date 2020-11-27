#include "OpenGLAssimpProcessor.h"
#include "../ResourceManagement/TextureResource.h"
#include "../Utility/FatalError.h"

OpenGL::OpenGLTextureHandler OpenGL::OpenGLAssimpProcessor::load_material(const aiMaterial* material, const aiTextureType texture_type, const std::string& directory){

	for(unsigned int i = 0; i < material->GetTextureCount(texture_type); i++){

		aiString ai_material_path;
		material->GetTexture(texture_type, i, &ai_material_path);

		std::string material_path{ ai_material_path.C_Str() };
		material_path = update_material_path(material_path, directory);
		
		TextureResource::load(material_path, material_path, true);
		load_material_into_handler(texture_type, material_path);
		
	}

	return m_texture_handler;
}

std::string OpenGL::OpenGLAssimpProcessor::update_material_path(const std::string& material_path, const std::string& directory){

	if (material_path.find('/') != std::string::npos || material_path.find('\\') != std::string::npos) {
		return material_path;
	} else {
		return material_path + "/" + directory;
	}
	
}

void OpenGL::OpenGLAssimpProcessor::load_material_into_handler(const aiTextureType texture_type, const std::string& material_name){

	switch (texture_type){

		case aiTextureType_DIFFUSE: {
			m_texture_handler.attach_diffuse_texture(material_name);
			break;
		}

		case aiTextureType_SPECULAR:{
			m_texture_handler.attach_specular_texture(material_name, 16.0f);
			break;
		}

		default:
			FatalError::fatal_error("OpenGLAssimpProcessor is loading a texture type that is not coded in!");							
	}
	
}
