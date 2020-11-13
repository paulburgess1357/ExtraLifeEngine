#include "InputHandler.h"
#include "InputManager.h"
#include "../Enums/Keyboard.h"
#include <GLFW/glfw3.h>

#include "../../Utility/Print.h"

InputHandler::InputHandler(Camera& camera)
	:m_camera{ camera },
	m_exit_command{ nullptr }{	
}

void InputHandler::hande_input() const{
	glfwPollEvents();

	if (InputManager<Keyboard>::is_pressed(Keyboard::ESCAPE)) {
		m_exit_command->execute();
	}

	handle_camera_movement();

	if (InputManager<Keyboard>::is_initial_press(Keyboard::F)) {
		m_camera.toggle_camera_type();
	}
}

void InputHandler::handle_camera_movement() const{

	if (InputManager<Keyboard>::is_pressed(Keyboard::W)) {
		m_camera.move(Direction::FORWARD);
	}

	if (InputManager<Keyboard>::is_pressed(Keyboard::S)) {
		m_camera.move(Direction::BACKWARD);
	}

	if (InputManager<Keyboard>::is_pressed(Keyboard::A)) {
		m_camera.move(Direction::LEFT);
	}

	if (InputManager<Keyboard>::is_pressed(Keyboard::D)) {
		m_camera.move(Direction::RIGHT);
	}

	if (InputManager<Keyboard>::is_pressed(Keyboard::Q)) {
		m_camera.move(Direction::VERTICAL_DOWN);
	}

	if (InputManager<Keyboard>::is_pressed(Keyboard::E)) {
		m_camera.move(Direction::VERTICAL_UP);
	}

	//if (InputManager<Keyboard>::is_initial_press(Keyboard::F)) {		
	//	m_camera.toggle_camera_type(); // causing crash
	//		
	//}
}

void InputHandler::set_exit(const std::shared_ptr<ICommand>& exit_command){
	m_exit_command = exit_command;
}