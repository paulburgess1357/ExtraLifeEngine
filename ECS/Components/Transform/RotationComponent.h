#pragma once
#include <glm/glm.hpp>

struct RotationComponent {

	RotationComponent(const float pitch_offset, const float yaw_offset, const float roll_offset, const float custom_axis_offset)
		:m_pitch_offset{ pitch_offset },
		m_yaw_offset{ yaw_offset },
		m_roll_offset{ roll_offset },
		m_rotation_offset{ custom_axis_offset}{
	}
	
	// Current orientation
	float m_current_pitch{ 0.0f };
	float m_current_yaw{ 0.0f };
	float m_current_roll{ 0.0f };
	float m_current_custom_rotation{ 0.0f };

	// Custom rotation axis
	glm::vec3 m_custom_rotation_axis{ 0.0f, 1.0f, 0.5f };

	// Rotation offset (degrees per frame)
	float m_pitch_offset{ 0.0f };
	float m_yaw_offset{ 0.0f };
	float m_roll_offset{ 0.0f };

	// Non-standard rotation axis
	float m_rotation_offset{ 0.0f };

};
