#pragma once
#include "../Environment/Interfaces/Shader/IShaderProgram.h"
#include <string>
#include <memory>
#include <unordered_map>

class ShaderResource {
	
public:
	ShaderResource() = default;
	~ShaderResource();
	void load(const std::string& shader_name, const std::string& vertex_shader_path, const std::string& fragment_shader_path, const bool set_default_lights = true);
	IShaderProgram* get(const std::string& shader_name);
	void destroy(const std::string& shader_name);
	void destroy_all();
	
private:		
	bool is_loaded(const std::string& shader_name);
	std::unordered_map<std::string, std::unique_ptr<IShaderProgram>> m_shader_cache;
	
};