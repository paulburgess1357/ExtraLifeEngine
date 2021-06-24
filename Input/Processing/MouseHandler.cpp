#include "MouseHandler.h"
#include "MouseManager.h"
#include "../Command/NullCommand.h"
#include <GLFW/glfw3.h>

MouseHandler::MouseHandler(Camera& camera)
	:m_camera{ camera },
	m_left_button_command(std::make_shared<NullCommand>()),
	m_right_button_command(std::make_shared<NullCommand>()),
	m_mouse_enabled{ false }{
	
}

void MouseHandler::handle_input() const{

	glfwPollEvents();	
	
	if(MouseManager::is_pressed(Mouse::LEFT_BUTTON)){
		m_left_button_command->execute();
	}

	if(MouseManager::is_pressed(Mouse::RIGHT_BUTTON)){
		m_right_button_command->execute();
	}

	if(!m_mouse_enabled){
		handle_camera_movement(m_camera);
	}
		
}

void MouseHandler::handle_camera_movement(Camera& camera) {
	camera.rotate(MouseManager::get_coords());
}

void MouseHandler::set_left_button(const std::shared_ptr<ICommand>& command){
	m_left_button_command = command;
}

void MouseHandler::set_right_button(const std::shared_ptr<ICommand>& command){
	m_right_button_command = command;
}

void MouseHandler::set_mouse_enabled(const bool mouse_enabled){	
	// Enabled in this context lines up with the windows definition of n
	// enabled.  When the mouse is enabled, it can move within and outside
	// the open window
	// When the mouse is not enabled, it means the engine (e.g. camera
	// movement) has control
	m_mouse_enabled = mouse_enabled;
	reset_camera_first_rotation_movement();
}

void MouseHandler::reset_camera_first_rotation_movement() const{
	m_camera.reset_first_rotation_movement();
}
