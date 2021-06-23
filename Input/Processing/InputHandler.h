#pragma once
#include "../Command/ICommand.h"
#include "../../Camera/Camera.h"
#include <memory>

class InputHandler {

public:
	InputHandler(Camera& camera);
	void hande_input() const;
	void set_exit(const std::shared_ptr<ICommand>& exit_command);
	void set_mouse_control(const std::shared_ptr<ICommand>& mouse_control_command);

private:
	void handle_camera_movement() const;
	Camera& m_camera;
	std::shared_ptr<ICommand> m_exit_command;
	std::shared_ptr<ICommand> m_camera_toggle_type_command;
	std::shared_ptr<ICommand> m_mouse_control_command;
};		
