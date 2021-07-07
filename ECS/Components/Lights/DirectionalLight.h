#pragma once
#include "ILight.h"
#include <glm/glm.hpp>

struct DirectionalLight : ILight{
	DirectionalLight(std::string light_name)
		:ILight{ std::move(light_name) }{		
	}
	glm::vec3 m_direction { 0.0f, 1.0f, 0.0f };
};
