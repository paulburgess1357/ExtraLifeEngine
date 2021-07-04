#pragma once
#include "../Texture/TextureShaderData.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include "../../Environment/Interfaces/Texture/ITextureHandler.h"
#include <string>
#include <unordered_map>

namespace OpenGL{
	
	class OpenGLTextureHandler : public ITextureHandler{

	public:
		OpenGLTextureHandler();
		OpenGLTextureHandler(IShaderProgram& shader_program);

		void attach_diffuse_texture(const std::string& texture_name) override;
		void attach_normal_texture(const std::string& texture_name) override;
		void attach_specular_texture(const std::string& texture_name, const float shininess) override;
		void attach_cubemap_texture(const std::string& texture_name) override;
		
		void bind_textures() const override;
		void unbind_textures() const override;
		
	private:
		void bind_diffuse_textures() const;
		void bind_specular_textures() const;
		void bind_normal_textures() const;
		void bind_cubemap_textures() const;

		void unbind_diffuse_textures() const;
		void unbind_specular_textures() const;
		void unbind_normal_textures() const;
		void unbind_cubemap_textures() const;
		
		void check_tex_unit() const;
		static void check_texture_qty(const unsigned int qty);

		// Texture maps
		// <texture_name, <texture_name_in_shader, tex_unit, tex_handle>
		unsigned int m_available_tex_unit;

		unsigned int m_current_diffuse;
		std::unordered_map<std::string, TextureShaderData> m_diffuse_texture_map;

		unsigned int m_current_specular;
		std::unordered_map<std::string, TextureShaderData> m_specular_texture_map;

		unsigned int m_current_normal;
		std::unordered_map<std::string, TextureShaderData> m_normal_texture_map;

		unsigned int m_current_cubemap;
		std::unordered_map<std::string, TextureShaderData> m_cubemap_texture_map;		
	};
	
} // namespace OpenGL


