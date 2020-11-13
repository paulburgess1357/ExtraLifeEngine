#include "MouseHandler.h"
#include "MouseManager.h"
#include <GLFW/glfw3.h>

MouseHandler::MouseHandler(Camera& camera)
	:m_camera{ camera },
	m_left_button_command(std::make_shared<NullCommand>()),
	m_right_button_command(std::make_shared<NullCommand>()) {
}

void MouseHandler::handle_input() const{

	glfwPollEvents();	
	
	if(MouseManager::is_pressed(Mouse::LEFT_BUTTON)){
		m_left_button_command->execute();
	}

	if(MouseManager::is_pressed(Mouse::RIGHT_BUTTON)){
		m_right_button_command->execute();
	}

	handle_camera_movement(m_camera);
	
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
