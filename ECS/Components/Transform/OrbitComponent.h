#pragma once
#include <glm/glm.hpp>

struct OrbitComponent{

	OrbitComponent(const glm::vec3& movement_from_center_axis, const glm::vec3& custom_orbit_axis, const float radius, const float orbit_offset)
		:m_movement_from_center_axis{ movement_from_center_axis },
		m_custom_orbit_axis{ custom_orbit_axis },
		m_radius{ radius },
		m_orbit_offset{ orbit_offset }{
	}

	OrbitComponent(const glm::vec3& movement_from_center_axis, const glm::vec3& custom_orbit_axis, const float radius, const float orbit_offset, const bool maintain_orientation)
		:m_movement_from_center_axis{ movement_from_center_axis },
		m_custom_orbit_axis{ custom_orbit_axis },
		m_radius{ radius },		
		m_orbit_offset{ orbit_offset },
		m_maintain_orientation{ maintain_orientation } {
	}
	
	// Current orientation
	float m_current_orbit{ 0.0f };
	
	// The orbit radius is moved from the origin using the axis below
	glm::vec3 m_movement_from_center_axis{ 0.0f, 0.0f, 1.0f };

	// Custom orbit rotation axis
	glm::vec3 m_custom_orbit_axis{ 0.0f, 0.0f, 1.0f };
	float m_radius{ 5.0f };

	// Orbit rotation offset
	float m_orbit_offset{ 0.0f };

	// When maintain orientation is true, counter rotation is applied
	// to the object to keep its orientation stable
	bool m_maintain_orientation{ false };
	float m_maintain_orientation_rotation_tracker{ 0.0f };
	
};
