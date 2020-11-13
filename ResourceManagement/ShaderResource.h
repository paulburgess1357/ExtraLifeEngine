#pragma once
#include "../Environment/Interfaces/Shader/IShaderProgram.h"
#include <string>
#include <memory>
#include <unordered_map>

class ShaderResource {
	
public:		
	static std::shared_ptr<IShaderProgram> load(const std::string& shader_name, const std::string& vertex_shader, const std::string& fragment_shader);
	static std::shared_ptr<IShaderProgram> get(const std::string& shader_name);
	static void destroy(const std::string& shader_name);
	static void destroy_all();
	
private:		
	ShaderResource() = default;
	static bool is_loaded(const std::string& shader_name);
	static std::unordered_map<std::string, std::shared_ptr<IShaderProgram>> m_shader_cache;
	
};