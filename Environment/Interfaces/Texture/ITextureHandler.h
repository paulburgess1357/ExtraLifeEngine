#pragma once
#include "../../Environment/Interfaces/Texture/ITexture.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"

class ITextureHandler{
	
public:
	ITextureHandler();
	ITextureHandler(IShaderProgram& shader_program);	
	virtual ~ITextureHandler() = default;

	void set_shader_program(IShaderProgram& shader_program);
	
	virtual void bind_textures() const = 0;
	virtual void unbind_textures() const = 0;
	
	virtual void attach_diffuse_texture(const ITexture& texture) = 0;
	virtual void attach_specular_texture(const ITexture& texture, const float shininess) = 0;
	virtual void attach_normal_texture(const ITexture& texture) = 0;
	virtual void attach_cubemap_texture(const ITexture& texture) = 0;
	
protected:
	// Leaving as a pointer for future hot-reloading of shaders
	IShaderProgram* m_shader_program;

};