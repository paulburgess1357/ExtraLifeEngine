#include "OpenGLAssimpProcessor.h"
#include "../ResourceManagement/TextureResource.h"
#include "../Utility/FatalError.h"

void OpenGL::OpenGLAssimpProcessor::load_all_materials(const aiMesh* mesh, const aiScene* scene, const std::string& directory, const std::shared_ptr<IShaderProgram>& shader_program){	
	
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];	
	load_material(material, aiTextureType_DIFFUSE, directory, shader_program);
	load_material(material, aiTextureType_SPECULAR, directory, shader_program);
	load_material(material, aiTextureType_HEIGHT, directory, shader_program);
}


void OpenGL::OpenGLAssimpProcessor::load_material(const aiMaterial* material, const aiTextureType texture_type, const std::string& directory, const std::shared_ptr<IShaderProgram>& shader_program){
	
	for(unsigned int i = 0; i < material->GetTextureCount(texture_type); i++){

		aiString ai_material_path;
		material->GetTexture(texture_type, i, &ai_material_path);

		std::string material_path{ ai_material_path.C_Str() };
		material_path = update_material_path(material_path, directory);
		
		TextureResource::load(material_path, false);
		load_material_into_shader(material_path, texture_type, shader_program);
		
	}

}

std::string OpenGL::OpenGLAssimpProcessor::update_material_path(const std::string& material_path, const std::string& directory){

	if (material_path.find('/') != std::string::npos || material_path.find('\\') != std::string::npos) {
		return material_path;
	} else {
		return directory + "/" + material_path;
	}
	
}

void OpenGL::OpenGLAssimpProcessor::load_material_into_shader(const std::string& material_name, const aiTextureType texture_type, const std::shared_ptr<IShaderProgram>& shader_program){

	switch (texture_type){

		case aiTextureType_DIFFUSE: {
			shader_program->attach_diffuse_texture(material_name);
			break;
		}

		case aiTextureType_SPECULAR: {
			shader_program->attach_specular_texture(material_name, 16.0f);
			break;
		}

		// Obj & Assimp does not use aiTextureType_Normals for normal maps (backpack obj example)
		case aiTextureType_NORMALS: {
			FatalError::fatal_error("Normal map texture type needs to be added (aiTextureType_NORMALS)");
			break;
		}
		
		case aiTextureType_HEIGHT: {
			shader_program->attach_normal_texture(material_name);
			break;
		}

		case aiTextureType_AMBIENT:{
			FatalError::fatal_error("Height map texture type needs to be added");
			break;
		}

		default:
			FatalError::fatal_error("OpenGLAssimpProcessor is loading a texture type that is not coded in!");							
	}
	
}
