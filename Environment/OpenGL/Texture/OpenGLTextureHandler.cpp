#include "OpenGLTextureHandler.h"
#include "../../Utility/FatalError.h"
#include "../../Environment/OpenGL/Shader/OpenGLShaderProgram.h"
#include "../../../ResourceManagement/GraphicsConstants.h"
#include <glad/glad.h>

OpenGL::OpenGLTextureHandler::OpenGLTextureHandler()
	:ITextureHandler{},
	 m_available_tex_unit { 0 },
	 m_current_diffuse{ 0 },
	 m_current_specular{ 0 },
     m_current_normal{ 0 },
	 m_current_cubemap{ 0 }{	
}

OpenGL::OpenGLTextureHandler::OpenGLTextureHandler(IShaderProgram& shader_program)
	:ITextureHandler{ shader_program },
	 m_available_tex_unit{ 0 },
	 m_current_diffuse{ 0 },
	 m_current_specular{ 0 },
	 m_current_normal{ 0 },
	 m_current_cubemap{ 0 }{
}

void OpenGL::OpenGLTextureHandler::attach_diffuse_texture(const ITexture& texture) {

	const std::string texture_name = texture.get_texture_name();
	const auto it = m_diffuse_texture_map.find(texture_name);
	if (it == m_diffuse_texture_map.end()) {
		
		check_tex_unit();
		check_texture_qty(m_current_diffuse);
		
		const TextureShaderData texture_shader_data{ "diffuse_material.m_sampler", m_available_tex_unit, texture.get_handle() };
		m_diffuse_texture_map[texture_name] = texture_shader_data;		
		m_shader_program->set_uniform(texture_shader_data.m_texture_name_in_shader, texture_shader_data.m_tex_unit, true);
		
		m_current_diffuse++;
		m_available_tex_unit++;
	}
	
}

void OpenGL::OpenGLTextureHandler::attach_normal_texture(const ITexture& texture) {

	const std::string texture_name = texture.get_texture_name();
	const auto it = m_normal_texture_map.find(texture_name);
	if (it == m_normal_texture_map.end()) {

		check_tex_unit();
		check_texture_qty(m_current_normal);
		
		const TextureShaderData texture_shader_data{ "normal_material.m_sampler", m_available_tex_unit, texture.get_handle() };
		m_normal_texture_map[texture_name] = texture_shader_data;
		m_shader_program->set_uniform(texture_shader_data.m_texture_name_in_shader, texture_shader_data.m_tex_unit, true);
				
		m_current_normal++;
		m_available_tex_unit++;
	}

}

void OpenGL::OpenGLTextureHandler::attach_specular_texture(const ITexture& texture, const float shininess){

	const std::string texture_name = texture.get_texture_name();
	const auto it = m_specular_texture_map.find(texture_name);
	if (it == m_specular_texture_map.end()) {

		check_tex_unit();
		check_texture_qty(m_current_specular);
		
		const TextureShaderData texture_shader_data{ "specular_material.m_sampler", m_available_tex_unit, texture.get_handle(), shininess };
		m_specular_texture_map[texture_name] = texture_shader_data;

		m_shader_program->set_uniform(texture_shader_data.m_texture_name_in_shader, texture_shader_data.m_tex_unit, true);
		m_shader_program->set_uniform("specular_material.m_shininess", texture_shader_data.m_shininess, true);			

		m_current_specular++;
		m_available_tex_unit++;
	}
	
}

void OpenGL::OpenGLTextureHandler::attach_cubemap_texture(const ITexture& texture){

	const std::string texture_name = texture.get_texture_name();
	const auto it = m_cubemap_texture_map.find(texture_name);
	if (it == m_cubemap_texture_map.end()) {

		check_tex_unit();
		check_texture_qty(m_current_cubemap);
		
		const TextureShaderData texture_shader_data{ "cubemap", m_available_tex_unit, texture.get_handle() };
		m_cubemap_texture_map[texture_name] = texture_shader_data;
		m_shader_program->set_uniform(texture_shader_data.m_texture_name_in_shader, texture_shader_data.m_tex_unit, true);
				
		m_current_cubemap++;
		m_available_tex_unit++;
	}
	
}

void OpenGL::OpenGLTextureHandler::bind_textures() const{
	bind_diffuse_textures();
	bind_specular_textures();
	bind_normal_textures();
	bind_cubemap_textures();
}

void OpenGL::OpenGLTextureHandler::bind_textures_fast() const {
	// No shader bind calls (called in render system instead)
	bind_diffuse_textures_fast();
	bind_specular_textures_fast();
	bind_normal_textures_fast();
	bind_cubemap_textures_fast();
}

void OpenGL::OpenGLTextureHandler::bind_diffuse_textures() const{

	for (const auto& texture : m_diffuse_texture_map) {

		m_shader_program->set_uniform(texture.second.m_texture_name_in_shader, texture.second.m_tex_unit);
		m_shader_program->bind();

		glActiveTexture(GL_TEXTURE0 + texture.second.m_tex_unit);
		glBindTexture(GL_TEXTURE_2D, texture.second.m_tex_handle);

	}
	
}

void OpenGL::OpenGLTextureHandler::bind_diffuse_textures_fast() const{
	// No shader bind calls (meant for bind_textures_fast only)
	for (const auto& texture : m_diffuse_texture_map) {
		glActiveTexture(GL_TEXTURE0 + texture.second.m_tex_unit);
		glBindTexture(GL_TEXTURE_2D, texture.second.m_tex_handle);
	}
}


void OpenGL::OpenGLTextureHandler::bind_specular_textures() const{

	for (const auto& texture : m_specular_texture_map) {

		m_shader_program->set_uniform(texture.second.m_texture_name_in_shader, texture.second.m_tex_unit);
		m_shader_program->set_uniform("specular_material.m_shininess", texture.second.m_shininess);
		m_shader_program->bind();

		glActiveTexture(GL_TEXTURE0 + texture.second.m_tex_unit);
		glBindTexture(GL_TEXTURE_2D, texture.second.m_tex_handle);

	}
	
}

void OpenGL::OpenGLTextureHandler::bind_specular_textures_fast() const{
	// No shader bind calls (meant for bind_textures_fast only)
	for (const auto& texture : m_specular_texture_map) {
		glActiveTexture(GL_TEXTURE0 + texture.second.m_tex_unit);
		glBindTexture(GL_TEXTURE_2D, texture.second.m_tex_handle);
	}
}


void OpenGL::OpenGLTextureHandler::bind_normal_textures() const{

	for (const auto& texture : m_normal_texture_map) {

		m_shader_program->set_uniform(texture.second.m_texture_name_in_shader, texture.second.m_tex_unit);
		m_shader_program->bind();

		glActiveTexture(GL_TEXTURE0 + texture.second.m_tex_unit);
		glBindTexture(GL_TEXTURE_2D, texture.second.m_tex_handle);

	}
	
}

void OpenGL::OpenGLTextureHandler::bind_normal_textures_fast() const{
	// No shader bind calls (meant for bind_textures_fast only)
	for (const auto& texture : m_normal_texture_map) {
		glActiveTexture(GL_TEXTURE0 + texture.second.m_tex_unit);
		glBindTexture(GL_TEXTURE_2D, texture.second.m_tex_handle);
	}
}


void OpenGL::OpenGLTextureHandler::bind_cubemap_textures() const{

	for (const auto& texture : m_cubemap_texture_map) {
		m_shader_program->set_uniform(texture.second.m_texture_name_in_shader, texture.second.m_tex_unit);
		m_shader_program->bind();

		glActiveTexture(GL_TEXTURE0 + texture.second.m_tex_unit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture.second.m_tex_handle);
	}
}

void OpenGL::OpenGLTextureHandler::bind_cubemap_textures_fast() const{
	// No shader bind calls (meant for bind_textures_fast only)
	for (const auto& texture : m_cubemap_texture_map) {
		glActiveTexture(GL_TEXTURE0 + texture.second.m_tex_unit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture.second.m_tex_handle);
	}
}


void OpenGL::OpenGLTextureHandler::unbind_textures() const{
	// Diffuse/Normal/Specular Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Cubemap
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void OpenGL::OpenGLTextureHandler::check_tex_unit() const{

	if (m_available_tex_unit == GraphicsConstants::UNINITIALIZED_VALUE) {
		FatalError::fatal_error("Your tex unit for shader handle: " + std::to_string(m_shader_program->get_handle()) + " is :" + std::to_string(GraphicsConstants::UNINITIALIZED_VALUE));
	}

	if (m_available_tex_unit > 16) {
		FatalError::fatal_error("Your tex unit for shader handle: " + std::to_string(m_shader_program->get_handle()) + " is greater than 16!  You have 16 textures for a single shader?");
	}
	
}

void OpenGL::OpenGLTextureHandler::check_texture_qty(const unsigned int qty){
	if (qty == 1) {
		FatalError::fatal_error("Texture quantity is >= 1 (0 is the starting count for your texture quantity)!  Shaders are currently not coded to accept more than one type of texture per shader.");
	}
}
