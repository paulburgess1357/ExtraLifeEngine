#pragma once
#include "../../Environment/Interfaces/Texture/ITexture.h"
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class IShaderProgram{

public:	
	IShaderProgram(const unsigned int handle);

	virtual ~IShaderProgram() = default;
	virtual void bind() const = 0;	
	virtual void unbind() const = 0;
	virtual void destroy() const = 0;
	[[nodiscard]] unsigned int get_handle() const;
	
	// Texture handling (per shader)		
	virtual void attach_diffuse_texture(const ITexture& texture) = 0;
	virtual void attach_normal_texture(const ITexture& texture) = 0;
	virtual void attach_specular_texture(const ITexture& texture, const float shininess) = 0;
	virtual void attach_cubemap_texture(const ITexture& texture) = 0;
	
	virtual void bind_textures() const = 0;
	virtual void bind_textures_fast() const = 0;
	virtual void unbind_textures() const = 0;	

	// Lighting
	virtual void attach_scene_light(const std::string& scenelight_name) = 0;
	virtual void attach_directional_light(const std::string& dirlight_name) = 0;
	virtual void attach_point_light(const std::string& pointlight_name) = 0;
	
	// Single Value Uniforms
	virtual void set_uniform(const std::string& uniform_name, const int value, const bool apply_binds = true) = 0;
	virtual void set_uniform(const std::string& uniform_name, const unsigned int value, const bool apply_binds = true) = 0;
	virtual void set_uniform(const std::string& uniform_name, const float value, const bool apply_binds = true) = 0;

	// Vector Uniforms
	virtual void set_uniform(const std::string& uniform_name, const glm::vec2& value, const bool apply_binds = true) = 0;
	virtual void set_uniform(const std::string& uniform_name, const glm::vec3& value, const bool apply_binds = true) = 0;
	virtual void set_uniform(const std::string& uniform_name, const glm::vec4& value, const bool apply_binds = true) = 0;

	// Matrix Uniforms		
	virtual void set_uniform(const std::string& uniform_name, const glm::mat3& value, const bool apply_binds = true) = 0;
	virtual void set_uniform(const std::string& uniform_name, const glm::mat4& value, const bool apply_binds = true) = 0;

	// Handler Initialization
	virtual void init_texture_handler() = 0;
	virtual void init_light_handler() = 0;

protected:	
	virtual int get_uniform(const std::string& uniform_name) = 0;	
	unsigned int m_handle;
	std::unordered_map<std::string, int> m_uniform_locations;
	
};