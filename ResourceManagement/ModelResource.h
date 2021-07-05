#pragma once
#include "TextureResource.h"
#include "../Model/Model/IModel.h"
#include "../Environment/Interfaces/Shader/IShaderProgram.h"
#include <string>
#include <memory>
#include <unordered_map>

class ModelResource{

public:
	ModelResource() = default;
	~ModelResource();
	[[nodiscard]] IModel* get(const std::string& model_name);
	void load(const std::string& model_name, const std::string& model_path, IShaderProgram& shader, TextureResource& texture_resource, const bool assimp_flip_uvs);
	void destroy(const std::string& model_name);
	void destroy_all();
	
private:
	[[nodiscard]] bool is_loaded(const std::string& model_name) const;
	void load_opengl_model(const std::string& model_name, const std::string& model_path, IShaderProgram& shader, TextureResource& texture_resource, const bool assimp_flip_uvs);
	void load_vulkan_model(const std::string& model_name, const std::string& model_path, IShaderProgram& shader, TextureResource& texture_resource, const bool assimp_flip_uvs);
	void load_model(const std::string& model_name, const std::string& model_path, IShaderProgram& shader, TextureResource& texture_resource, const bool assimp_flip_uvs);
	
	std::unordered_map<std::string, std::unique_ptr<IModel>> m_model_cache;
};
