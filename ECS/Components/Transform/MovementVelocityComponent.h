#pragma once
#include <glm/glm.hpp>

struct MovementVelocityComponent {
	// x, y, z, movement velocity
	glm::vec3 m_movement_velocity{ 0.0f, 0.0f, 0.0f };
};