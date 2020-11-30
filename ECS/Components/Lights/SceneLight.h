#pragma once
#include <glm/glm.hpp>

struct SceneLight{
	glm::vec3 m_ambient{ 0.2f };
	glm::vec3 m_diffuse{ 0.5f };
	glm::vec3 m_specular{ 1.0f };
};