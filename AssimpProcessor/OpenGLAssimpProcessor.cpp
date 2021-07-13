#include "OpenGLAssimpProcessor.h"
#include "../ResourceManagement/TextureResource.h"
#include "../Utility/FatalError.h"
#include "../Utility/Print.h"

void OpenGL::OpenGLAssimpProcessor::load_all_materials(const aiMesh* assimp_mesh, const aiScene* scene, const std::string& directory, OpenGLMesh& mesh, TextureResource& texture_resource){	
	aiMaterial* material = scene->mMaterials[assimp_mesh->mMaterialIndex];	
	load_material(material, aiTextureType_DIFFUSE, directory, mesh, texture_resource);
	load_material(material, aiTextureType_SPECULAR, directory, mesh, texture_resource);
	load_material(material, aiTextureType_HEIGHT, directory, mesh, texture_resource);
	load_material(material, aiTextureType_NORMALS, directory, mesh, texture_resource);
	load_material(material, aiTextureType_AMBIENT, directory, mesh, texture_resource);
}


void OpenGL::OpenGLAssimpProcessor::load_material(const aiMaterial* material, const aiTextureType texture_type, const std::string& directory, OpenGLMesh& mesh, TextureResource& texture_resource){
	
	for(unsigned int i = 0; i < material->GetTextureCount(texture_type); i++){

		aiString ai_material_path;
		material->GetTexture(texture_type, i, &ai_material_path);

		std::string material_path{ ai_material_path.C_Str() };
		
		material_path = update_material_path(material_path, directory);

		if(texture_type == aiTextureType_DIFFUSE){
			// Gamma correction applied to diffuse textures
			texture_resource.load_model_textures(material_path, true);
		} else{
			// No gamma correction applied (e.g. lighting maps and such)
			texture_resource.load_model_textures(material_path, false);
		}
		

		
		const ITexture* mesh_texture = texture_resource.get(material_path);
		load_material_into_mesh(material_path, texture_type, mesh, *mesh_texture);
		
	}

}

std::string OpenGL::OpenGLAssimpProcessor::update_material_path(const std::string& material_path, const std::string& directory){

	//TODO add directory to material path here
	
	//if (material_path.find('/') != std::string::npos || material_path.find('\\') != std::string::npos) {
	//	return material_path;
	//} else {
		return directory + "/" + material_path;
	//}
	
}

void OpenGL::OpenGLAssimpProcessor::load_material_into_mesh(const std::string& material_name, const aiTextureType texture_type, OpenGLMesh& mesh, const ITexture& mesh_texture){

	switch (texture_type){

		case aiTextureType_DIFFUSE: {
			mesh.attach_diffuse_texture(mesh_texture);
			break;
		}

		case aiTextureType_SPECULAR: {
			mesh.attach_specular_texture(mesh_texture);
			break;
		}

		// Obj & Assimp does not use aiTextureType_Normals for normal maps (backpack obj example)
		case aiTextureType_NORMALS: {
			mesh.attach_normal_texture(mesh_texture);
			break;
		}
		
		case aiTextureType_HEIGHT: {
			Print::print("************* WARNING: Loading aiTextureType_HEIGHT AS attach_normal_texture() ; Typically this is for obj and output from Blender *************");
			mesh.attach_normal_texture(mesh_texture);
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
