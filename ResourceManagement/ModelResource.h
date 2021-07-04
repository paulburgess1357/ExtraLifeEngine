#pragma once
#include "../Model/Model/IModel.h"
#include "../Environment/Interfaces/Shader/IShaderProgram.h"
#include <string>
#include <memory>
#include <unordered_map>

class ModelResource{

public:
	static std::shared_ptr<IModel> load(const std::string& model_name, const std::string& model_path, IShaderProgram& shader, const bool assimp_flip_uvs);
	static std::shared_ptr<IModel> get(const std::string& model_name);
	static void destroy(const std::string& model_name);
	static void destroy_all();
	
private:
	ModelResource() = default;
	static bool is_loaded(const std::string& model_name);

	static void load_opengl_model(const std::string& model_name, const std::string& model_path, IShaderProgram& shader, const bool assimp_flip_uvs);
	static void load_vulkan_model(const std::string& model_name, const std::string& model_path, IShaderProgram& shader, const bool assimp_flip_uvs);
	static void load_model(const std::string& model_name, const std::string& model_path, IShaderProgram& shader, const bool assimp_flip_uvs);
	
	static std::unordered_map<std::string, std::shared_ptr<IModel>> m_model_cache;
};
