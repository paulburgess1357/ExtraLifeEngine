#include "InputHandler.h"
#include "InputManager.h"
#include "../Enums/Keyboard.h"
#include <GLFW/glfw3.h>

InputHandler::InputHandler(Camera& camera)
	:m_camera{ camera },
	 m_exit_command{ nullptr },
	 m_mouse_control_command{ nullptr },
	 m_imgui_display_command{ nullptr }{
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

	if(InputManager<Keyboard>::is_initial_press(Keyboard::LEFT_CONTROL)){
		m_mouse_control_command->execute();
		m_imgui_display_command->execute();
	}

	if(InputManager<Keyboard>::is_initial_press(Keyboard::F7)){
		m_wireframe_mode_command->execute();
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

}

void InputHandler::set_exit(const std::shared_ptr<ICommand>& exit_command){
	m_exit_command = exit_command;
}

void InputHandler::set_mouse_control(const std::shared_ptr<ICommand>& mouse_control_command){
	m_mouse_control_command = mouse_control_command;
}

void InputHandler::set_wireframe_mode(const std::shared_ptr<ICommand>& wireframe_mode_command){
	m_wireframe_mode_command = wireframe_mode_command;
}

void InputHandler::set_imgui_display(const std::shared_ptr<ICommand>& imgui_display_command){
	m_imgui_display_command = imgui_display_command;
}
