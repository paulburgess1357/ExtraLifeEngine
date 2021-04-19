#include "IWindowCreator.h"
#include "../../Utility/Print.h"
#include "../../Utility/FatalError.h"
#include "../../Input/Enums/Keyboard.h"
#include "../../Neutral/API/GraphicsAPI.h"
#include "../../Input/Processing/InputManager.h"
#include "../../Input/Processing/MouseManager.h"
#include "../../OpenGL/Window/OpenGLWindowCreator.h"

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

std::shared_ptr<IWindow> IWindowCreator::create_window(const int width, const int height, const bool is_resizeable) {

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		std::unique_ptr<IWindowCreator> window_creator = std::make_unique<OpenGL::OpenGLWindowCreator>(width, height, is_resizeable);
		return window_creator->create_glfw_window();
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan window creation method does not exist!");
		std::shared_ptr<IWindow> window_creator = nullptr;
		return window_creator;
	}

	FatalError::fatal_error("Unknown Graphics API Type.  Cannot return window.");
	std::shared_ptr<IWindow> window_creator = nullptr;
	return window_creator;
}