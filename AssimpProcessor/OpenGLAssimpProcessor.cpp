#include "OpenGLAssimpProcessor.h"
#include "../ResourceManagement/TextureResource.h"
#include "../Utility/FatalError.h"

void OpenGL::OpenGLAssimpProcessor::load_all_materials(const aiMesh* assimp_mesh, const aiScene* scene, const std::string& directory, OpenGLMesh& mesh){	
	aiMaterial* material = scene->mMaterials[assimp_mesh->mMaterialIndex];	
	load_material(material, aiTextureType_DIFFUSE, directory, mesh);
	load_material(material, aiTextureType_SPECULAR, directory, mesh);
	load_material(material, aiTextureType_HEIGHT, directory, mesh);
}


void OpenGL::OpenGLAssimpProcessor::load_material(const aiMaterial* material, const aiTextureType texture_type, const std::string& directory, OpenGLMesh& mesh){
	
	for(unsigned int i = 0; i < material->GetTextureCount(texture_type); i++){

		aiString ai_material_path;
		material->GetTexture(texture_type, i, &ai_material_path);

		std::string material_path{ ai_material_path.C_Str() };
		material_path = update_material_path(material_path, directory);
		
		TextureResource::load_model_textures(material_path);
		load_material_into_mesh(material_path, texture_type, mesh);
		
	}

}

std::string OpenGL::OpenGLAssimpProcessor::update_material_path(const std::string& material_path, const std::string& directory){

	if (material_path.find('/') != std::string::npos || material_path.find('\\') != std::string::npos) {
		return material_path;
	} else {
		return directory + "/" + material_path;
	}
	
}

void OpenGL::OpenGLAssimpProcessor::load_material_into_mesh(const std::string& material_name, const aiTextureType texture_type, OpenGLMesh& mesh){

	switch (texture_type){

		case aiTextureType_DIFFUSE: {
			mesh.attach_diffuse_texture(material_name);
			break;
		}

		case aiTextureType_SPECULAR: {
			mesh.attach_specular_texture(material_name);
			break;
		}

		// Obj & Assimp does not use aiTextureType_Normals for normal maps (backpack obj example)
		case aiTextureType_NORMALS: {
			FatalError::fatal_error("Normal map texture type needs to be added (aiTextureType_NORMALS)");
			break;
		}
		
		case aiTextureType_HEIGHT: {
			mesh.attach_normal_texture(material_name);
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
