#include "OpenGLAssimpProcessor.h"
#include "../ResourceManagement/TextureResource.h"
#include "../Utility/FatalError.h"

OpenGL::OpenGLTextureHandler OpenGL::OpenGLAssimpProcessor::load_all_materials(const aiMesh* mesh, const aiScene* scene, const std::string& directory, const std::shared_ptr<IShaderProgram>& shader_program){	
	
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	OpenGLTextureHandler texture_handler;
	texture_handler.set_shader_program(shader_program);
	
	load_material(texture_handler, material, aiTextureType_DIFFUSE, directory);
	load_material(texture_handler, material, aiTextureType_SPECULAR, directory);
	load_material(texture_handler, material, aiTextureType_HEIGHT, directory);
	return texture_handler;	
}


void OpenGL::OpenGLAssimpProcessor::load_material(OpenGLTextureHandler& texture_handler, const aiMaterial* material, const aiTextureType texture_type, const std::string& directory){
	
	for(unsigned int i = 0; i < material->GetTextureCount(texture_type); i++){

		aiString ai_material_path;
		material->GetTexture(texture_type, i, &ai_material_path);

		std::string material_path{ ai_material_path.C_Str() };
		material_path = update_material_path(material_path, directory);
		
		TextureResource::load(material_path, false);
		load_material_into_handler(texture_handler, material_path, texture_type);
		
	}

}

std::string OpenGL::OpenGLAssimpProcessor::update_material_path(const std::string& material_path, const std::string& directory){

	if (material_path.find('/') != std::string::npos || material_path.find('\\') != std::string::npos) {
		return material_path;
	} else {
		return directory + "/" + material_path;
	}
	
}

void OpenGL::OpenGLAssimpProcessor::load_material_into_handler(OpenGLTextureHandler& texture_handler, const std::string& material_name, const aiTextureType texture_type){

	switch (texture_type){

		case aiTextureType_DIFFUSE: {
			texture_handler.attach_diffuse_texture(material_name);
			break;
		}

		case aiTextureType_SPECULAR: {
			texture_handler.attach_specular_texture(material_name, 16.0f);
			break;
		}

		// Obj & Assimp does not use aiTextureType_Normals for normal maps (backpack obj example)
		case aiTextureType_NORMALS: {
			FatalError::fatal_error("Normal map texture type needs to be added (aiTextureType_NORMALS)");
			break;
		}
		
		case aiTextureType_HEIGHT: {
			//Print::print("****** Warning: Attaching normal texture using 'aiTextureType_HEIGHT' ******");
			texture_handler.attach_normal_texture(material_name);
			break;
		}

		case aiTextureType_AMBIENT:{
			//TODO confirm this is a height map
			FatalError::fatal_error("Height map texture type needs to be added");
			break;
		}

		default:
			FatalError::fatal_error("OpenGLAssimpProcessor is loading a texture type that is not coded in!");							
	}
	
}
