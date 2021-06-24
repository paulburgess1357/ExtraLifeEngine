#include "CameraData.h"
#include <glm/gtc/matrix_transform.hpp>

CameraData::CameraData(const glm::vec3& camera_position, const glm::vec3& camera_forward)
	:m_camera_position{ camera_position },
	m_camera_forward{ camera_forward },
	m_camera_up{ 0.0f, 1.0f, 0.0f },
	m_camera_right{ glm::normalize(glm::cross(m_camera_up, m_camera_forward)) },
	m_world_up{ 0.0f, 1.0f, 0.0f },
	m_view_matrix{ 1.0f },
	m_view_matrix_needs_update{ true } {
	
}

glm::vec3 CameraData::get_camera_position() const{
	return m_camera_position;
}

glm::vec3 CameraData::get_camera_forward() const{
	return m_camera_forward;
}

glm::mat4 CameraData::get_view_matrix() {
	if(m_view_matrix_needs_update){
		m_view_matrix = glm::lookAt(
			m_camera_position,
			m_camera_position + m_camera_forward,
			m_camera_up
		);
	}
	m_view_matrix_needs_update = false;
	return m_view_matrix;
}
