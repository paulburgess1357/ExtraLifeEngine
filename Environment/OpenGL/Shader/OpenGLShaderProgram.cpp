#include "OpenGLShaderProgram.h"
#include "../../Utility/Print.h"
#include "../../Utility/FatalError.h"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

OpenGL::OpenGLShaderProgram::OpenGLShaderProgram(const std::string& shader_name, const unsigned int handle)
	:IShaderProgram{ shader_name, handle }{
}

void OpenGL::OpenGLShaderProgram::bind() const{
	glUseProgram(m_handle);
}

void OpenGL::OpenGLShaderProgram::unbind() const{
	glUseProgram(0);
}

void OpenGL::OpenGLShaderProgram::destroy() const{	
	Print::print("Destroying Shader Program: " + get_shader_name() + " (Handle: " + std::to_string(m_handle) + ")");
	glDeleteProgram(m_handle);
}

int OpenGL::OpenGLShaderProgram::get_uniform(const std::string& uniform_name) {
	const auto it = m_uniform_locations.find(uniform_name);
	if (it == m_uniform_locations.end()) {
		m_uniform_locations[uniform_name] = glGetUniformLocation(m_handle, uniform_name.c_str());

		if(m_uniform_locations[uniform_name] == -1){
			FatalError::fatal_error("Invalid uniform variable name: '" + uniform_name + "'. This variable has not been found in the current shader (glsl code) program: " + m_shader_name);
		}		
	}
	
	return m_uniform_locations.at(uniform_name);
}

void OpenGL::OpenGLShaderProgram::set_uniform(const std::string& uniform_name, const int value) {
	bind();
	glUniform1i(get_uniform(uniform_name), value);
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



