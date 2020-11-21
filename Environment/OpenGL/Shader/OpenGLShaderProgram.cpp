#include "OpenGLShaderProgram.h"
#include "../../Utility/Print.h"
#include "../../Utility/FatalError.h"
#include "../../ResourceManagement/LightResource.h"
#include "../../ResourceManagement/TextureResource.h"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

//std::unordered_map<std::string, std::pair<std::string, std::shared_ptr<DirectionalLight>>> OpenGL::OpenGLShaderProgram::m_directional_light_map;

OpenGL::OpenGLShaderProgram::OpenGLShaderProgram(const unsigned int handle)
	:IShaderProgram{ handle },
	m_available_tex_unit{ 0 },
	m_current_dirlight{ 0 }{
}

void OpenGL::OpenGLShaderProgram::bind() const{
	glUseProgram(m_handle);
}

void OpenGL::OpenGLShaderProgram::unbind() const{
	glUseProgram(0);
}

void OpenGL::OpenGLShaderProgram::attach_diffuse_texture(const std::string& texture_name) {

	const auto it = m_texture_map.find(texture_name);
	if (it == m_texture_map.end()) {		

		check_tex_unit();
		const std::shared_ptr<ITexture> texture = TextureResource::get(texture_name);
		m_texture_map[texture_name] = std::make_pair(m_available_tex_unit, texture->get_handle());

		Print::print("Attaching diffuse texture '" + texture_name + "' (material.diffuse) to shader handle: " + std::to_string(m_handle));
		set_uniform("material.diffuse", m_available_tex_unit);
		
		m_available_tex_unit++;
	}

}

void OpenGL::OpenGLShaderProgram::attach_specular_texture(const std::string& texture_name, const float shininess) {

	const auto it = m_texture_map.find(texture_name);
	if (it == m_texture_map.end()) {

		check_tex_unit();
		const std::shared_ptr<ITexture> texture = TextureResource::get(texture_name);
		m_texture_map[texture_name] = std::make_pair(m_available_tex_unit, texture->get_handle());

		Print::print("Attaching specular texture '" + texture_name + "' (material.specular) to shader handle: " + std::to_string(m_handle));
		set_uniform("material.specular", m_available_tex_unit);
		set_uniform("material.shininess", shininess);

		m_available_tex_unit++;
	}

}

void OpenGL::OpenGLShaderProgram::attach_directional_light(const std::string& dirlight_name){

	const std::string dirlight_shader_name = "dirlight[" + std::to_string(m_current_dirlight) + "]";

	m_directional_light_map[dirlight_name].first = dirlight_shader_name;
	m_directional_light_map[dirlight_name].second = LightResource::get_dirlight(dirlight_name);

	Print::print("Attaching Directional Light: " + dirlight_name + " (" + dirlight_shader_name + ")");
	set_uniform(dirlight_shader_name + ".direction", m_directional_light_map[dirlight_name].second->direction);
	set_uniform("active_dirlight_qty", m_current_dirlight);
	m_current_dirlight++;
	
}

void OpenGL::OpenGLShaderProgram::attach_scene_light(const std::string& scenelight_name){

	Print::print("Attaching Scene Light: " + scenelight_name);
	m_scene_light_pair.first = scenelight_name;
	m_scene_light_pair.second = LightResource::get_scenelight(scenelight_name);

	set_uniform("scenelight.ambient", m_scene_light_pair.second->ambient);
	set_uniform("scenelight.diffuse", m_scene_light_pair.second->diffuse);
	set_uniform("scenelight.specular", m_scene_light_pair.second->specular);
	
}


void OpenGL::OpenGLShaderProgram::check_tex_unit() const {
	if (m_available_tex_unit == 99) {
		FatalError::fatal_error("Your tex unit for shader handle: " + std::to_string(m_handle) + " is 99");
	}

	if (m_available_tex_unit > 16) {
		FatalError::fatal_error("Your tex unit for shader handle: " + std::to_string(m_handle) + " is greater than 16!  You have 16 textures for a single shader?");
	}
}

void OpenGL::OpenGLShaderProgram::bind_textures() const {

	for (const auto& texture : m_texture_map) {
		glActiveTexture(GL_TEXTURE0 + texture.second.first);
		glBindTexture(GL_TEXTURE_2D, texture.second.second);
	}
}

void OpenGL::OpenGLShaderProgram::unbind_textures() const {
	for (const auto& texture : m_texture_map) {
		glActiveTexture(GL_TEXTURE0 + texture.second.first);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void OpenGL::OpenGLShaderProgram::destroy() const{	
	Print::print("Destroying Shader Program: (Handle: " + std::to_string(m_handle) + ")");
	glDeleteProgram(m_handle);
}

int OpenGL::OpenGLShaderProgram::get_uniform(const std::string& uniform_name) {
	const auto it = m_uniform_locations.find(uniform_name);
	if (it == m_uniform_locations.end()) {
		m_uniform_locations[uniform_name] = glGetUniformLocation(m_handle, uniform_name.c_str());

		if(m_uniform_locations[uniform_name] == -1){
			FatalError::fatal_error("Invalid uniform variable name: '" + uniform_name + "'. This variable has not been found in the current shader (GLSL code) program handle: " + std::to_string(m_handle));
		}		
	}
	
	return m_uniform_locations.at(uniform_name);
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const int value) {
	bind();
	glUniform1i(get_uniform(uniform_name), value);
	unbind();
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const unsigned int value) {
	bind();
	glUniform1i(get_uniform(uniform_name), static_cast<int>(value));
	unbind();
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const float value) {
	bind();
	glUniform1f(get_uniform(uniform_name), value);
	unbind();
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const glm::vec2& value) {
	bind();
	glUniform2f(get_uniform(uniform_name), value.x, value.y);
	unbind();
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const glm::vec3& value) {
	bind();
	glUniform3f(get_uniform(uniform_name), value.x, value.y, value.z);
	unbind();
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const glm::vec4& value) {
	bind();
	glUniform4f(get_uniform(uniform_name), value.x, value.y, value.z, value.w);
	unbind();
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const glm::mat3& value) {
	bind();	
	glUniformMatrix3fv(get_uniform(uniform_name), 1, GL_FALSE, glm::value_ptr(value));
	unbind();
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const glm::mat4& value) {
	bind();
	glUniformMatrix4fv(get_uniform(uniform_name), 1, GL_FALSE, glm::value_ptr(value));
	unbind();
}