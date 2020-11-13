#include "IWindowCreator.h"
#include "../../Utility/Print.h"
#include "../../Input/Processing/InputManager.h"
#include "../../Input/Processing/MouseManager.h"
#include "../../Input/Enums/Keyboard.h"

IWindowCreator::IWindowCreator()
		:m_window{ nullptr } {
}

void IWindowCreator::init_glfw() {
	Print::print("Initializing GLFW");
	if (!glfwInit()) {
		std::cerr << "GLFW failed to initialize" << std::endl;
	}
}

void IWindowCreator::init_glfw_window(const int width, const int height) {
	Print::print("Creating GLFW OpenGLWindow");
	m_window = glfwCreateWindow(width, height, "ExtraLifeEngine", nullptr, nullptr);

	if (!m_window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
	}
}

void IWindowCreator::init_glfw_input() const {
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, true);
	glfwSetInputMode(m_window, GLFW_STICKY_MOUSE_BUTTONS, true);
}

void IWindowCreator::init_callbacks() const {
	glfwSetKeyCallback(m_window, InputManager<Keyboard>::window_callback);
	glfwSetMouseButtonCallback(m_window, MouseManager::mouse_button_callback);
	glfwSetCursorPosCallback(m_window, MouseManager::mouse_position_callback);
	glfwSetCursorEnterCallback(m_window, MouseManager::mouse_within_window_callback);
}

void IWindowCreator::init_vsync() {
	glfwSwapInterval(true);
}

void IWindowCreator::center_mouse() const{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
