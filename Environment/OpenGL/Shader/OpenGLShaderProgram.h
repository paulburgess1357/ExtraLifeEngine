#pragma once
#include "../../Interfaces/Shader/IShaderProgram.h"
#include "../../ECS/Components/Lights/DirectionalLight.h"
#include "../../ECS/Components/Lights/SceneLight.h"
#include "../../ECS/Components/Lights/PointLight.h"
#include <unordered_map>
#include <utility>
#include <memory>

namespace OpenGL{

	class OpenGLShaderProgram : public IShaderProgram{
		
	public:		
		OpenGLShaderProgram(const unsigned int handle);
		
		void bind() const override;
		void unbind() const override;
		void destroy() const override;

		// Texture handling (per shader)		
		void attach_diffuse_texture(const std::string& texture_name) override;
		void attach_specular_texture(const std::string& texture_name, const float shininess) override;
		void bind_textures() const override;
		void unbind_textures() const override;
		void check_tex_unit() const;

		// Lighting
		void attach_scene_light(const std::string& scenelight_name) override;
		void attach_directional_light(const std::string& dirlight_name) override;

		// Single Value Uniforms
		void set_uniform(const std::string& uniform_name, const int value) override;
		void set_uniform(const std::string& uniform_name, const unsigned int value) override;
		void set_uniform(const std::string& uniform_name, const float value) override;

		// Vector Uniforms
		void set_uniform(const std::string& uniform_name, const glm::vec2& value) override;
		void set_uniform(const std::string& uniform_name, const glm::vec3& value) override;
		void set_uniform(const std::string& uniform_name, const glm::vec4& value) override;

		// Matrix Uniforms		
		void set_uniform(const std::string& uniform_name, const glm::mat3& value) override;
		void set_uniform(const std::string& uniform_name, const glm::mat4& value) override;

	private:
		int get_uniform(const std::string& uniform_name) override;

		// Texture map
		// <texture_name, <tex_unit, tex_handle>>
		unsigned int m_available_tex_unit;
		std::unordered_map<std::string, std::pair<unsigned int, unsigned int>> m_texture_map;

		// Directional light map
		// < actual light name, < light name in shader, shared ptr to light>>
		unsigned int m_current_dirlight;		
		std::unordered_map<std::string, std::pair<std::string, std::shared_ptr<DirectionalLight>>> m_directional_light_map;

		// Scene light
		std::pair<std::string, std::shared_ptr<SceneLight>> m_scene_light_pair;
		
		// Point light map
		// std::unordered_map<std::string, std::shared_ptr<PointLight>> m_point_light_map;		
	};
	
} // namespace OpenGL



