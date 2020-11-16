#include "ShaderResource.h"
#include "../Utility/FatalError.h"
#include "../Environment/Interfaces/Shader/IShaderLoader.h"
#include "../Environment/Neutral/Shader/ShaderLoaderFromFile.h"
#include "../Environment/OpenGL/Shader/OpenGLShaderCompiler.h"
#include "../Utility/Print.h"

std::unordered_map<std::string, std::shared_ptr<IShaderProgram>> ShaderResource::m_shader_cache;

std::shared_ptr<IShaderProgram> ShaderResource::load(const std::string& shader_name, const std::string& vertex_shader_path, const std::string& fragment_shader_path){
	if (!is_loaded(shader_name)) {
		const std::shared_ptr<IShaderLoader> shader_loader = std::make_shared<ShaderLoaderFromFile>(vertex_shader_path, fragment_shader_path);
		const std::shared_ptr<IShaderCompiler> shader_compiler = std::make_shared<OpenGL::OpenGLShaderCompiler>(shader_loader);
		m_shader_cache[shader_name] = shader_compiler->compile();;
	}	
	return m_shader_cache[shader_name];
}

bool ShaderResource::is_loaded(const std::string& shader_name){
	const auto it = m_shader_cache.find(shader_name);
	if (it == m_shader_cache.end()) {
		return false;
	} 
	return true;
}

std::shared_ptr<IShaderProgram> ShaderResource::get(const std::string& shader_name){
	if (!is_loaded(shader_name)) {
		FatalError::fatal_error("Unable to locate shader: " + shader_name);
	}
	return m_shader_cache.at(shader_name);
}

void ShaderResource::destroy(const std::string& shader_name){
	if (!is_loaded(shader_name)) {
		FatalError::fatal_error("Unable to locate and destroy shader: " + shader_name);
	}
	Print::print("Destroying Shader: " + shader_name);
	m_shader_cache.at(shader_name)->destroy();
	m_shader_cache.erase(shader_name);
}

void ShaderResource::destroy_all(){
	for(auto& shader : m_shader_cache){
		Print::print("Destroying Shader: " + shader.first);
		shader.second->destroy();
	}
	m_shader_cache.clear();
}