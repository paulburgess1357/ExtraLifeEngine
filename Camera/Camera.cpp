#include "Camera.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& camera_position, const glm::vec3& camera_forward, float movement_speed, float look_sensitivity)
	:CameraData(camera_position, camera_forward),
	m_movement_speed{ movement_speed },
	m_look_sensitivity{ look_sensitivity },
	m_camera_type{ CameraType::FIXED_LEVEL_HORIZON },
	m_camera_type_toggle { CameraType::FIXED_LEVEL_HORIZON, CameraType::FREE },
	m_camera_type_toggle_tracker { 1 },
	m_old_mouse_coords{ 0.0f, 0.0f },
	m_first_rotation_movement{ true }{
	
}

void Camera::move(const Direction direction) {

	set_vertical_movement_axis();

	switch (direction) {

		case Direction::FORWARD:
			move_forward();
			break;

		case Direction::BACKWARD:
			move_backward();
			break;

		case Direction::LEFT:
			move_left();
			break;

		case Direction::RIGHT:
			move_right();
			break;

		case Direction::VERTICAL_UP:
			move_vertical_up();
			break;

		case Direction::VERTICAL_DOWN:
			move_vertical_down();
			break;

		default:
			break;
	}

	m_view_matrix_needs_update = true;
}

void Camera::set_vertical_movement_axis(){
	if (m_camera_type == CameraType::FIXED_LEVEL_HORIZON) {
		m_vertical_movement_axis = glm::normalize(glm::cross(m_camera_forward, m_camera_right));
	} else {
		m_vertical_movement_axis = m_camera_up;
	}
}

void Camera::move_forward(){
	m_camera_position += m_camera_forward * m_movement_speed;
}

void Camera::move_backward(){
	m_camera_position -= m_camera_forward * m_movement_speed;
}

void Camera::move_left(){
	m_camera_position += m_camera_right * m_movement_speed;
}

void Camera::move_right(){
	m_camera_position -= m_camera_right * m_movement_speed;
}

void Camera::move_vertical_up(){
	m_camera_position += m_vertical_movement_axis * m_movement_speed;
}

void Camera::move_vertical_down(){
	m_camera_position += -m_vertical_movement_axis * m_movement_speed;
}

void Camera::rotate(const glm::vec2& current_mouse_coords) {

	// Handles mouse movement from user location to center (removes fast frame movement)
	if (m_first_rotation_movement) {
		set_first_mouse_movement(current_mouse_coords);
	} else {
		const glm::vec2 mouse_delta = (current_mouse_coords - m_old_mouse_coords) * m_look_sensitivity;

		// Handle yaw/pitch based on camera mode
		if (m_camera_type == CameraType::FREE) {
			pitch(-mouse_delta.y);
			roll(mouse_delta.x);
		} else {
			pitch(-mouse_delta.y);
			yaw(-mouse_delta.x);
		}
	}

	if (m_old_mouse_coords != current_mouse_coords) {
		m_view_matrix_needs_update = true;
	}
	
	m_old_mouse_coords = current_mouse_coords;	
}

void Camera::set_first_mouse_movement(const glm::vec2& current_mouse_coords){
	if (current_mouse_coords.x != 0 && current_mouse_coords.y != 0) {
		m_first_rotation_movement = false;
	}
}

void Camera::pitch(float angle_offset) {

	// Pitch Rotation Component
	m_current_pitch += angle_offset;

	// Clamp pitch if forcing level horizon
	if (m_camera_type == CameraType::FIXED_LEVEL_HORIZON) {
		if (m_current_pitch > 85.0f || m_current_pitch < -85.0f) {
			m_current_pitch -= angle_offset;
			angle_offset = 0;
		}
	}

	// Calculate rotation
	const glm::quat pitch_quaternion = glm::angleAxis(glm::radians(-angle_offset), m_camera_right);
	m_camera_forward = glm::normalize(glm::rotate(pitch_quaternion, m_camera_forward));

	// Update Vectors
	m_camera_up = glm::normalize(glm::rotate(pitch_quaternion, m_camera_up));
}

void Camera::roll(const float angle_offset) {

	// Allow roll for free flying camera (i.e. spaceship style camera)
	if (m_camera_type == CameraType::FREE) {

		// Roll Rotation Component
		const glm::quat roll_quaternion = glm::angleAxis(glm::radians(angle_offset), m_camera_forward);

		// Update Vectors
		m_camera_right = glm::normalize(glm::rotate(roll_quaternion, m_camera_right));
		m_camera_up = glm::normalize(glm::rotate(roll_quaternion, m_camera_up));
	}
}

void Camera::yaw(const float angle_offset) {

	// Set yaw axis (local or world)
	if (m_camera_type == CameraType::FIXED_LEVEL_HORIZON) {
		m_camera_up = m_world_up;
	}

	// Yaw Rotation Component
	const glm::quat yaw_quaternion = glm::angleAxis(glm::radians(angle_offset), m_camera_up);

	// Update Vectors
	m_camera_right = glm::normalize(glm::rotate(yaw_quaternion, m_camera_right));
	m_camera_forward = glm::normalize(glm::rotate(yaw_quaternion, m_camera_forward));
}

void Camera::toggle_camera_type() {
	if (m_camera_type_toggle_tracker >= static_cast<int>(m_camera_type_toggle.size())) {
		m_camera_type_toggle_tracker = 0;
	}

	set_camera_type(m_camera_type_toggle.at(m_camera_type_toggle_tracker));
	m_camera_type_toggle_tracker++;
	m_view_matrix_needs_update = true;
}

void Camera::set_camera_type(const CameraType camera_type) {
	m_camera_type = camera_type;

	switch (camera_type) {

		case CameraType::FIXED_LEVEL_HORIZON: {
			reset_orientation_fixed_horizon();
			break;
		}

		case CameraType::FREE: {
			reset_orientation_free();
			break;
		}

		default:
			break;
	}
}

void Camera::reset_orientation_fixed_horizon(){
	m_current_pitch = 0;
	m_camera_up = m_world_up;

	// Save current view orientation but level camera
	m_camera_forward.y = 0;
	m_camera_right = glm::normalize(glm::cross(m_camera_up, m_camera_forward));
}

void Camera::reset_orientation_free(){
	m_camera_up = glm::normalize(glm::cross(m_camera_forward, m_camera_right));
	m_vertical_movement_axis = m_camera_up;
}
