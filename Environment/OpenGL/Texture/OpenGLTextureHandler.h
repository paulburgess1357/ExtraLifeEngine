#pragma once
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <string>
#include <memory>
#include <unordered_map>

namespace OpenGL{
	
	class OpenGLTextureHandler{

	public:
		OpenGLTextureHandler();

		void attach_diffuse_texture(const std::string& texture_name);
		void attach_specular_texture(const std::string& texture_name, const float shininess);
		
		void bind_textures() const;
		void unbind_textures() const;
		void set_shader_program(const std::shared_ptr<IShaderProgram>& shader_program);
		
	private:
		void check_tex_unit() const;
		static void check_texture_qty(const unsigned int qty);

		// Texture maps
		// <texture_name, <tex_unit, tex_handle>>
		unsigned int m_available_tex_unit;

		unsigned int m_current_diffuse;
		std::unordered_map<std::string, std::pair<unsigned int, unsigned int>> m_diffuse_texture_map;

		unsigned int m_current_specular;
		std::unordered_map<std::string, std::pair<unsigned int, unsigned int>> m_specular_texture_map;

		std::shared_ptr<IShaderProgram> m_shader_program;
		
	};
	
} // namespace OpenGL


