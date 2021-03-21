#include "ModelResource.h"
#include "../Utility/Print.h"
#include "../Utility/FatalError.h"
#include "../Model/Model/OpenGLModel.h"
#include "../ResourceManagement/ShaderResource.h"
#include "../Environment/Neutral/API/GraphicsAPI.h"
#include "../Environment/Neutral/API/GraphicsAPIType.h"

std::unordered_map<std::string, std::shared_ptr<IModel>> ModelResource::m_model_cache;

std::shared_ptr<IModel> ModelResource::load(const std::string& model_name, const std::string& model_path, const std::string& shader_name, const bool assimp_flip_uvs){
	if(!is_loaded(model_name)){		
		Print::print("\nLoading Model: " + model_name + " (" + model_path + ")");
		load_model(model_name, model_path, shader_name, assimp_flip_uvs);
	}
	return m_model_cache[model_name];
}

bool ModelResource::is_loaded(const std::string& model_name) {
	const auto it = m_model_cache.find(model_name);
	if (it == m_model_cache.end()) {
		return false;
	}
	return true;
}

void ModelResource::load_model(const std::string& model_name, const std::string& model_path, const std::string& shader_name, const bool assimp_flip_uvs) {

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		load_opengl_model(model_name, model_path, shader_name, assimp_flip_uvs);
		return;
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		load_vulkan_model(model_name, model_path, shader_name, assimp_flip_uvs);
		return;
	}

	FatalError::fatal_error("Unknown graphics API type.  Cannot load model into resource.");
}


void ModelResource::load_opengl_model(const std::string& model_name, const std::string& model_path, const std::string& shader_name, const bool assimp_flip_uvs) {
	
	const std::shared_ptr<IShaderProgram> shader_program = ShaderResource::get(shader_name);
	OpenGL::OpenGLModelLoaderFromFile model_loader{ model_path, shader_program, assimp_flip_uvs };
	m_model_cache[model_name] = std::make_shared<OpenGL::OpenGLModel>(model_loader);
}

void ModelResource::load_vulkan_model(const std::string& model_name, const std::string& model_path, const std::string& shader_name, const bool assimp_flip_uvs) {
	FatalError::fatal_error("Vulkan model code is not set for the model resource loader!");
}

std::shared_ptr<IModel> ModelResource::get(const std::string& model_name){
	if (!is_loaded(model_name)) {
		FatalError::fatal_error("Unable to locate model: " + model_name);
	}
	return m_model_cache.at(model_name);
}

void ModelResource::destroy(const std::string& model_name){

	if (!is_loaded(model_name)) {
		FatalError::fatal_error("Unable to locate and destroy shader: " + model_name);
	}
	Print::print("Destroying Model: " + model_name);

	m_model_cache.at(model_name)->destroy();
	m_model_cache.erase(model_name);
	
}

void ModelResource::destroy_all(){
	for(auto& model : m_model_cache){
		Print::print("Destroying Model: " + model.first);
		model.second->destroy();
		model.second->destroy_mesh_vector();
	}	
}


