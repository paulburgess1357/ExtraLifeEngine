#pragma once
#include "../../Interfaces/Shader/IShaderProgram.h"
#include <unordered_map>
#include <utility>

namespace OpenGL{

	class OpenGLShaderProgram : public IShaderProgram{
		
	public:		
		OpenGLShaderProgram(const unsigned int handle);
		
		void bind() const override;
		void unbind() const override;
		void destroy() const override;

		// Single Value Uniforms
		void set_uniform(const std::string& uniform_name, const int value) override;
		void set_uniform(const std::string& uniform_name, const float value) override;

		// Vector Uniforms
		void set_uniform(const std::string& uniform_name, const glm::vec2& value) override;
		void set_uniform(const std::string& uniform_name, const glm::vec3& value) override;
		void set_uniform(const std::string& uniform_name, const glm::vec4& value) override;

		// Matrix Uniforms		
		void set_uniform(const std::string& uniform_name, const glm::mat3& value) override;
		void set_uniform(const std::string& uniform_name, const glm::mat4& value) override;

		// Texture handling (per shader)
		void check_tex_unit() const;
		void attach_texture(const std::string& texture_name) override;
		void bind_textures() const override;
		void unbind_textures() const override;

	private:
		int get_uniform(const std::string& uniform_name) override;

		// Texture map
		// <texture_name, <tex_unit, tex_handle>>
		unsigned int m_available_tex_unit;
		std::unordered_map<std::string, std::pair<unsigned int, unsigned int>> m_texture_map;
		
	};
	
} // namespace OpenGL



