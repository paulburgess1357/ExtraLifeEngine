#include "../../Environment/OpenGL/Shader/OpenGLShaderProgram.h"
#include "OpenGLTextureHandler.h"
#include "../../Utility/Print.h"
#include "../../Utility/FatalError.h"
#include "../../ResourceManagement/TextureResource.h"
#include <glad/glad.h>

OpenGL::OpenGLTextureHandler::OpenGLTextureHandler()
	:m_available_tex_unit { 0 },
	 m_current_diffuse{ 0 },
	 m_current_specular{ 0 },
	 m_shader_program{ nullptr }{
	
}

void OpenGL::OpenGLTextureHandler::attach_diffuse_texture(const std::string& texture_name){

	const auto it = m_diffuse_texture_map.find(texture_name);
	if (it == m_diffuse_texture_map.end()) {

		check_tex_unit();
		const std::shared_ptr<ITexture> texture = TextureResource::get(texture_name);
		m_diffuse_texture_map[texture_name] = std::make_pair(m_available_tex_unit, texture->get_handle());

		Print::print("Attaching diffuse texture '" + texture_name + "' (diffuse_material.m_sampler) to shader handle: " + std::to_string(m_shader_program->get_handle()));
		m_shader_program->set_uniform("diffuse_material.m_sampler", m_available_tex_unit);

		check_texture_qty(m_current_diffuse);

		m_current_diffuse++;
		m_available_tex_unit++;
	}
	
}

void OpenGL::OpenGLTextureHandler::attach_specular_texture(const std::string& texture_name, const float shininess){

	const auto it = m_specular_texture_map.find(texture_name);
	if (it == m_specular_texture_map.end()) {

		check_tex_unit();
		const std::shared_ptr<ITexture> texture = TextureResource::get(texture_name);
		m_specular_texture_map[texture_name] = std::make_pair(m_available_tex_unit, texture->get_handle());

		Print::print("Attaching specular texture '" + texture_name + "' (specular_material.m_sampler) to shader handle: " + std::to_string(m_shader_program->get_handle()));
		m_shader_program->set_uniform("specular_material.m_sampler", m_available_tex_unit);
		m_shader_program->set_uniform("specular_material.m_shininess", shininess);

		check_texture_qty(m_current_specular);

		m_current_specular++;
		m_available_tex_unit++;
	}
	
}

void OpenGL::OpenGLTextureHandler::bind_textures() const{

	for (const auto& texture : m_diffuse_texture_map) {
		glActiveTexture(GL_TEXTURE0 + texture.second.first);
		glBindTexture(GL_TEXTURE_2D, texture.second.second);
	}

	for (const auto& texture : m_specular_texture_map) {
		glActiveTexture(GL_TEXTURE0 + texture.second.first);
		glBindTexture(GL_TEXTURE_2D, texture.second.second);
	}
	
}

void OpenGL::OpenGLTextureHandler::unbind_textures() const{

	for (const auto& texture : m_diffuse_texture_map) {
		glActiveTexture(GL_TEXTURE0 + texture.second.first);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	for (const auto& texture : m_specular_texture_map) {
		glActiveTexture(GL_TEXTURE0 + texture.second.first);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
}

void OpenGL::OpenGLTextureHandler::check_tex_unit() const{

	if (m_available_tex_unit == 99) {
		FatalError::fatal_error("Your tex unit for shader handle: " + std::to_string(m_shader_program->get_handle()) + " is 99");
	}

	if (m_available_tex_unit > 16) {
		FatalError::fatal_error("Your tex unit for shader handle: " + std::to_string(m_shader_program->get_handle()) + " is greater than 16!  You have 16 textures for a single shader?");
	}
	
}

void OpenGL::OpenGLTextureHandler::check_texture_qty(const unsigned qty){
	if (qty == 1) {
		FatalError::fatal_error("Texture quantity is >= 1 (0 is the starting count for your texture quantity)!  Shaders are currently not coded to accept more than one type of texture per shader.");
	}
}

void OpenGL::OpenGLTextureHandler::set_shader_program(const std::shared_ptr<IShaderProgram>& shader_program){
	m_shader_program = shader_program;
}


