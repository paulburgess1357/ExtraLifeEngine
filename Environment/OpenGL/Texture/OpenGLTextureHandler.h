#pragma once
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include "../Texture/TextureShaderData.h"
#include <string>
#include <memory>
#include <unordered_map>

namespace OpenGL{
	
	class OpenGLTextureHandler{

	public:
		OpenGLTextureHandler();

		void attach_diffuse_texture(const std::string& texture_name);
		void attach_normal_texture(const std::string& texture_name);
		void attach_specular_texture(const std::string& texture_name, const float shininess);
		
		void bind_textures() const;
		void unbind_textures() const;
		void set_shader_program(const std::shared_ptr<IShaderProgram>& shader_program);
		
	private:

		void bind_diffuse_textures() const;
		void bind_specular_textures() const;
		void bind_normal_textures() const;

		void unbind_diffuse_textures() const;
		void unbind_specular_textures() const;
		void unbind_normal_textures() const;
		
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

		std::shared_ptr<IShaderProgram> m_shader_program;
		
	};
	
} // namespace OpenGL


