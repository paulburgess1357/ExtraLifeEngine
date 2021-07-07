#pragma once
#include "../../ECS/Components/Lights/SceneLight.h"
#include "../../ECS/Components/Lights/PointLight.h"
#include "../../ECS/Components/Lights/DirectionalLight.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <string>
#include <unordered_map>

namespace OpenGL{
	
	class OpenGLLightHandler {

	public:
		OpenGLLightHandler();
		
		void attach_scene_light(const SceneLight& scene_light);
		void attach_directional_light(const DirectionalLight& dirlight);
		void attach_point_light(const PointLight& pointlight);
		void set_shader_program(IShaderProgram& shader_program);

	private:
		static std::string create_shader_variable_name(const std::string& name, const unsigned int index);
		
		// Directional light map
		// < actual light name, < light name in shader, pointer to light>>
		unsigned int m_current_dirlight;
		std::unordered_map<std::string, std::pair<std::string, const DirectionalLight*>> m_directional_light_map;

		// Scene light		
		std::pair<std::string, const SceneLight*> m_scene_light_pair;

		// Point light map
		unsigned int m_current_pointlight;
		std::unordered_map<std::string, std::pair<std::string, const PointLight*>> m_pointlight_map;

		// Leaving as a pointer for future hot-reloading of shaders
		IShaderProgram* m_shader_program;
	};
	
} // namespace OpenGL
