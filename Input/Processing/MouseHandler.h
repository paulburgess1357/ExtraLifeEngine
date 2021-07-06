#pragma once
#include "../Command/ICommand.h"
#include "../../Camera/Camera.h"
#include <memory>

class MouseHandler {

public:
	MouseHandler(Camera& camera);
	
	void handle_input() const;
	void set_left_button(std::unique_ptr<ICommand> command);
	void set_right_button(std::unique_ptr<ICommand> command);

	void set_mouse_enabled(const bool mouse_enabled);
	void reset_camera_first_rotation_movement() const;
	
private:
	static void handle_camera_movement(Camera& camera);	
	Camera& m_camera;
	std::unique_ptr<ICommand> m_left_button_command;
	std::unique_ptr<ICommand> m_right_button_command;
	bool m_mouse_enabled;
};

