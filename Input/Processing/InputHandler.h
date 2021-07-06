#pragma once
#include "../Command/ICommand.h"
#include "../../Camera/Camera.h"
#include <memory>

class InputHandler {

public:
	InputHandler(Camera& camera);
	void handle_input() const;
	void set_exit(std::unique_ptr<ICommand> exit_command);
	void set_mouse_control(std::unique_ptr<ICommand> mouse_control_command);
	void set_wireframe_mode(std::unique_ptr<ICommand> wireframe_mode_command);
	void set_imgui_display(std::unique_ptr<ICommand> imgui_display_command);
	
private:
	void handle_camera_movement() const;
	Camera& m_camera;
	std::unique_ptr<ICommand> m_exit_command;
	std::unique_ptr<ICommand> m_camera_toggle_type_command;
	std::unique_ptr<ICommand> m_mouse_control_command;
	std::unique_ptr<ICommand> m_wireframe_mode_command;
	std::unique_ptr<ICommand> m_imgui_display_command;
};		
