#pragma once
#include "../Light/OpenGLLightHandler.h"
#include "../Texture/OpenGLTextureHandler.h"
#include "../../Interfaces/Shader/IShaderProgram.h"
#include <unordered_map>
#include <memory>

namespace OpenGL{

	class OpenGLShaderProgram : public IShaderProgram, public std::enable_shared_from_this<OpenGLShaderProgram> {
		
	public:		
		OpenGLShaderProgram(const unsigned int handle);
		
		void bind() const override;
		void unbind() const override;
		void destroy() const override;

		// Texture handling (per shader)		
		void attach_diffuse_texture(const std::string& texture_name) override;
		void attach_normal_texture(const std::string& texture_name) override;
		void attach_specular_texture(const std::string& texture_name, const float shininess) override;
		void attach_cubemap_texture(const std::string& texture_name) override;
		
		void bind_textures() const override;
		void unbind_textures() const override;		

		// Lighting
		void attach_scene_light(const std::string& scenelight_name) override;
		void attach_directional_light(const std::string& dirlight_name) override;
		void attach_point_light(const std::string& pointlight_name) override;

		// Single Value Uniforms
		void set_uniform(const std::string& uniform_name, const int value, const bool apply_binds = true) override;
		void set_uniform(const std::string& uniform_name, const unsigned int value, const bool apply_binds = true) override;
		void set_uniform(const std::string& uniform_name, const float value, const bool apply_binds = true) override;

		// Vector Uniforms
		void set_uniform(const std::string& uniform_name, const glm::vec2& value, const bool apply_binds = true) override;
		void set_uniform(const std::string& uniform_name, const glm::vec3& value, const bool apply_binds = true) override;
		void set_uniform(const std::string& uniform_name, const glm::vec4& value, const bool apply_binds = true) override;

		// Matrix Uniforms		
		void set_uniform(const std::string& uniform_name, const glm::mat3& value, const bool apply_binds = true) override;
		void set_uniform(const std::string& uniform_name, const glm::mat4& value, const bool apply_binds = true) override;

		// Handler initialization
		void init_texture_handler() override;
		void init_light_handler() override;

	private:			
		int get_uniform(const std::string& uniform_name) override;

		// Texture Handler
		OpenGLTextureHandler m_texture_handler;

		// Light Handler
		OpenGLLightHandler m_light_handler;
	};
	
} // namespace OpenGL



