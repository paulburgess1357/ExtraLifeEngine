#pragma once
#include "ILight.h"
#include <glm/glm.hpp>

struct SceneLight : ILight{

	SceneLight(std::string light_name)
		:ILight{ std::move(light_name) }{		
	}
	
	glm::vec3 m_ambient{ 0.6f };
	glm::vec3 m_diffuse{ 0.5f };
	glm::vec3 m_specular{ 1.0f };

	// Ambient: E.g. moonlight
	// Diffuse: Directional impact of light on an object (the more the face 'faces' the light source, the brighter it becomes)
	// Specular: The bright spot of light that appears on shiny objects
};