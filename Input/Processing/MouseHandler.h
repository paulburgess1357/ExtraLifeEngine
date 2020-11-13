#pragma once
#include "../Command/ICommand.h"
#include "../Command/NullCommand.h"
#include "../../Camera/Camera.h"
#include <memory>

class MouseHandler {

public:
	MouseHandler(Camera& camera);
	
	void handle_input() const;
	void set_left_button(const std::shared_ptr<ICommand>& command);
	void set_right_button(const std::shared_ptr<ICommand>& command);
	
private:
	static void handle_camera_movement(Camera& camera);
	Camera& m_camera;
	std::shared_ptr<ICommand> m_left_button_command;
	std::shared_ptr<ICommand> m_right_button_command;
};

