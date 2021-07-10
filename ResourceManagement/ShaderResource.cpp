#include "ShaderResource.h"
#include "../Utility/FatalError.h"
#include "../Environment/Interfaces/Shader/IShaderLoader.h"
#include "../Environment/Neutral/Shader/ShaderLoaderFromFile.h"
#include "../Environment/OpenGL/Shader/OpenGLShaderCompiler.h"
#include "../Utility/Print.h"

ShaderResource::~ShaderResource(){
	destroy_all();
}

void ShaderResource::load(const std::string& shader_name, const std::string& vertex_shader_path, const std::string& fragment_shader_path, const bool link_uniform_blocks){
	if (!is_loaded(shader_name)) {
		Print::print("\nLoading Shader: " + shader_name + " (" + vertex_shader_path + ") & (" + fragment_shader_path + ")");
		const std::unique_ptr<IShaderLoader> shader_loader = std::make_unique<ShaderLoaderFromFile>(vertex_shader_path, fragment_shader_path);
		const std::unique_ptr<IShaderCompiler> shader_compiler = IShaderCompiler::create_compiler(*shader_loader);		
		m_shader_cache[shader_name] = shader_compiler->compile(link_uniform_blocks);
	}	
}

bool ShaderResource::is_loaded(const std::string& shader_name) const{
	return m_shader_cache.count(shader_name) > 0;
}

IShaderProgram* ShaderResource::get(const std::string& shader_name){
	if (!is_loaded(shader_name)) {
		FatalError::fatal_error("Unable to locate shader: " + shader_name);
	}
	return m_shader_cache.at(shader_name).get();
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
	Print::print("Destroying ShaderResource");
	for(auto& shader : m_shader_cache){
		Print::print("        - Destroying Shader: " + shader.first);
		shader.second->destroy();
	}
	m_shader_cache.clear();
}

void ShaderResource::display_initialized_shader_variables() const{
	Print::print("\nInitialized Shader Variables: ");
	for(auto& shader : m_shader_cache){
		Print::print(" - " + shader.first);
		shader.second->show_initialized_shader_variables();
		shader.second->check_uniforms_in_shader_code_are_initialized();
		Print::print("\n-------------------------------------------------\n");
	}
	Print::print("\n");
}
