#pragma once
#include "ILight.h"
#include <glm/glm.hpp>

struct DirectionalLight : ILight{
	DirectionalLight(std::string light_name)
		:ILight{ std::move(light_name) }{		
	}	
	DirectionalLight(std::string light_name, const glm::vec3& light_direction)
		:ILight{ std::move(light_name) },
		 m_direction{ light_direction }{		
	}
	glm::vec3 m_direction { 0.5f, 0.5f, 0.0f };
};
