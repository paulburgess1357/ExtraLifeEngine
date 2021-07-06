#pragma once
#include "CameraData.h"
#include "CameraType.h"
#include "Direction.h"
#include <glm/glm.hpp>
#include <vector>

class Camera : public CameraData {
	
public:
	Camera(const glm::vec3& camera_position, const glm::vec3& camera_forward, float movement_speed, float look_sensitivity);
	void move(const Direction direction);
	void rotate(const glm::vec2& current_mouse_coords);
	void toggle_camera_type();
	void reset_first_rotation_movement();
	void set_camera_speed(const float movement_speed);
		
private:
	void pitch(const float angle_offset);
	void yaw(const float angle_offset);
	void roll(const float angle_offset);
	
	void reset_orientation_free();
	void reset_orientation_fixed_horizon();

	void set_camera_type(const CameraType camera_type);	
	void set_first_mouse_movement(const glm::vec2& current_mouse_coords);
	
	void move_forward();
	void move_backward();
	void move_left();
	void move_right();
	void move_vertical_up();
	void move_vertical_down();
	void set_vertical_movement_axis();
	
	float m_movement_speed;
	float m_look_sensitivity;
	float m_current_pitch;
	glm::vec3 m_vertical_movement_axis;
	CameraType m_camera_type;
	
	std::vector<CameraType> m_camera_type_toggle;
	int m_camera_type_toggle_tracker;
	
	glm::vec2 m_old_mouse_coords;
	bool m_first_rotation_movement;
};

