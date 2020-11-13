#pragma once
#include <glm/glm.hpp>

class CameraData{

public:
	CameraData(const glm::vec3& camera_position, const glm::vec3& camera_forward);
	
	glm::vec3 get_camera_position() const;
	glm::vec3 get_camera_forward() const;
	glm::mat4 get_view_matrix();
	
protected:	
	glm::vec3 m_camera_position;
	glm::vec3 m_camera_forward;
	glm::vec3 m_camera_up;
	glm::vec3 m_camera_right;

	glm::vec3 m_world_up;
	glm::mat4 m_view_matrix;
	bool m_view_matrix_needs_update;
	
};

