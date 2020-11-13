#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class IShaderProgram{

public:
	IShaderProgram()
		:m_shader_name{ "No Name" },
		m_handle{ 99 }{		
	}
	
	IShaderProgram(const std::string& shader_name, const unsigned int handle)
		:m_shader_name{ shader_name },
		m_handle{ handle }{
	}

	virtual ~IShaderProgram() = default;
	virtual void bind() const = 0;	
	virtual void unbind() const = 0;
	virtual void destroy() const = 0;

	std::string get_shader_name() const{
		return m_shader_name;
	}
	
	// Single Value Uniforms
	virtual void set_uniform(const std::string& uniform_name, const int value) = 0;
	virtual void set_uniform(const std::string& uniform_name, const float value) = 0;

	// Vector Uniforms
	virtual void set_uniform(const std::string& uniform_name, const glm::vec2& value) = 0;
	virtual void set_uniform(const std::string& uniform_name, const glm::vec3& value) = 0;
	virtual void set_uniform(const std::string& uniform_name, const glm::vec4& value) = 0;

	// Matrix Uniforms		
	virtual void set_uniform(const std::string& uniform_name, const glm::mat3& value) = 0;
	virtual void set_uniform(const std::string& uniform_name, const glm::mat4& value) = 0;

protected:
	virtual int get_uniform(const std::string& uniform_name) = 0;
	
	std::string m_shader_name;
	unsigned int m_handle;
	std::unordered_map<std::string, int> m_uniform_locations;
	
};