#pragma once
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <memory>

class ITextureHandler{
	
public:
	ITextureHandler();
	ITextureHandler(const std::shared_ptr<IShaderProgram>& shader_program);
	virtual ~ITextureHandler() = default;
	virtual void bind_textures() const = 0;
	virtual void unbind_textures() const = 0;
	
	virtual void attach_diffuse_texture(const std::string& texture_name) = 0;
	virtual void attach_specular_texture(const std::string& texture_name, const float shininess) = 0;
	virtual void attach_normal_texture(const std::string& texture_name) = 0;
	virtual void attach_cubemap_texture(const std::string& texture_name) = 0;
	virtual void set_shader_program(const std::shared_ptr<IShaderProgram>& shader_program);
	
protected:
	std::shared_ptr<IShaderProgram> m_shader_program;
};