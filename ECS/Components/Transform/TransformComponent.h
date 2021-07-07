#pragma once
#include <glm/glm.hpp>
	
struct TransformComponent {
	
	TransformComponent(const glm::vec3& world_position)
		:m_world_position{ world_position },
		m_model_matrix{ glm::mat4(1) }{
	}

	glm::vec3 m_world_position;
	glm::mat4 m_model_matrix;
	
};
