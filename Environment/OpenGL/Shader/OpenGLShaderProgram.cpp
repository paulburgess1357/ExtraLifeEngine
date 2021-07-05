#include "OpenGLShaderProgram.h"
#include "../../Utility/Print.h"
#include "../../Utility/FatalError.h"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

OpenGL::OpenGLShaderProgram::OpenGLShaderProgram(const unsigned int handle)
	:IShaderProgram{ handle }{
}

void OpenGL::OpenGLShaderProgram::bind() const{
	glUseProgram(m_handle);
}

void OpenGL::OpenGLShaderProgram::unbind() const{
	glUseProgram(0);
}

void OpenGL::OpenGLShaderProgram::destroy() const {
	Print::print("Destroying Shader Program: (Handle: " + std::to_string(m_handle) + ")");
	glDeleteProgram(m_handle);
}

void OpenGL::OpenGLShaderProgram::attach_diffuse_texture(const ITexture& texture) {
	m_texture_handler.attach_diffuse_texture(texture);
}

void OpenGL::OpenGLShaderProgram::attach_normal_texture(const ITexture& texture) {
	m_texture_handler.attach_normal_texture(texture);
}

void OpenGL::OpenGLShaderProgram::attach_specular_texture(const ITexture& texture, const float shininess) {
	m_texture_handler.attach_specular_texture(texture, shininess);
}

void OpenGL::OpenGLShaderProgram::attach_cubemap_texture(const ITexture& texture){
	m_texture_handler.attach_cubemap_texture(texture);
}

void OpenGL::OpenGLShaderProgram::bind_textures() const {
	m_texture_handler.bind_textures();
}

void OpenGL::OpenGLShaderProgram::bind_textures_fast() const{
	m_texture_handler.bind_textures_fast();
}

void OpenGL::OpenGLShaderProgram::unbind_textures() const {
	m_texture_handler.unbind_textures();
}

void OpenGL::OpenGLShaderProgram::attach_scene_light(const SceneLight& scene_light) {
	m_light_handler.attach_scene_light(scene_light);
}

void OpenGL::OpenGLShaderProgram::attach_directional_light(const DirectionalLight& dirlight) {
	m_light_handler.attach_directional_light(dirlight);
}

void OpenGL::OpenGLShaderProgram::attach_point_light(const PointLight& pointlight) {
	m_light_handler.attach_point_light(pointlight);
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const int value, const bool apply_binds) {
	if(apply_binds){
		bind();
		glUniform1i(get_uniform(uniform_name), value);
		unbind();
	} else{
		glUniform1i(get_uniform(uniform_name), value);
	}
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const unsigned int value, const bool apply_binds) {
	if (apply_binds) {
		bind();
		glUniform1i(get_uniform(uniform_name), static_cast<int>(value));
		unbind();
	} else{
		glUniform1i(get_uniform(uniform_name), static_cast<int>(value));
	}
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const float value, const bool apply_binds) {
	if(apply_binds){
		bind();
		glUniform1f(get_uniform(uniform_name), value);
		unbind();
	} else{
		glUniform1f(get_uniform(uniform_name), value);
	}
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const glm::vec2& value, const bool apply_binds) {
	if(apply_binds){
		bind();
		glUniform2f(get_uniform(uniform_name), value.x, value.y);
		unbind();
	} else{
		glUniform2f(get_uniform(uniform_name), value.x, value.y);
	}
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const glm::vec3& value, const bool apply_binds) {
	if(apply_binds){
		bind();
		glUniform3f(get_uniform(uniform_name), value.x, value.y, value.z);
		unbind();
	} else{
		glUniform3f(get_uniform(uniform_name), value.x, value.y, value.z);
	}
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const glm::vec4& value, const bool apply_binds) {
	if(apply_binds){
		bind();
		glUniform4f(get_uniform(uniform_name), value.x, value.y, value.z, value.w);
		unbind();
	} else{
		glUniform4f(get_uniform(uniform_name), value.x, value.y, value.z, value.w);
	}
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const glm::mat3& value, const bool apply_binds) {
	if(apply_binds){
		bind();
		glUniformMatrix3fv(get_uniform(uniform_name), 1, GL_FALSE, glm::value_ptr(value));
		unbind();
	} else{
		glUniformMatrix3fv(get_uniform(uniform_name), 1, GL_FALSE, glm::value_ptr(value));
	}
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const glm::mat4& value, const bool apply_binds) {
	if(apply_binds){
		bind();
		glUniformMatrix4fv(get_uniform(uniform_name), 1, GL_FALSE, glm::value_ptr(value));
		unbind();
	} else{
		glUniformMatrix4fv(get_uniform(uniform_name), 1, GL_FALSE, glm::value_ptr(value));
	}
}

void OpenGL::OpenGLShaderProgram::init_texture_handler(){
	m_texture_handler.set_shader_program(*this);
}

void OpenGL::OpenGLShaderProgram::init_light_handler(){
	m_light_handler.set_shader_program(*this);
}

int OpenGL::OpenGLShaderProgram::get_uniform(const std::string& uniform_name) {
	const auto it = m_uniform_locations.find(uniform_name);
	if (it == m_uniform_locations.end()) {
		m_uniform_locations[uniform_name] = glGetUniformLocation(m_handle, uniform_name.c_str());

		if (m_uniform_locations[uniform_name] == -1) {
			//FatalError::fatal_error("Invalid uniform variable name: '" + uniform_name + "'. This variable has not been found in the current shader (GLSL code) program handle: " + std::to_string(m_handle));
		}
	}

	return m_uniform_locations.at(uniform_name);
}
