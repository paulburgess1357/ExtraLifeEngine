#include "IWindow.h"

int IWindow::m_width{ 0 };
int IWindow::m_height{ 0 };
bool IWindow::m_is_resizeable{ true };
bool IWindow::m_mouse_enabled{ true };
GLFWwindow* IWindow::m_window{ nullptr };

IWindow::IWindow(const int width, const int height, const bool is_resizeable, const bool mouse_enabled, GLFWwindow* window) {
	m_width = width;
	m_height = height;
	m_is_resizeable = is_resizeable;
	m_mouse_enabled = mouse_enabled;
	m_window = window;

	if (mouse_enabled) {
		enable_mouse();
	} else {
		disable_mouse();
	}
}

IWindow::~IWindow() {
	glfwDestroyWindow(m_window);
}

GLFWwindow* IWindow::get_glfw_ptr() {
	return m_window;
}

int IWindow::get_width() {
	return m_width;
}

int IWindow::get_height() {
	return m_height;
}

bool IWindow::get_mouse_enabled() {
	return m_mouse_enabled;
}


bool IWindow::is_resizeable() {
	return m_is_resizeable;
}

void IWindow::toggle_mouse() {
	if (m_mouse_enabled) {
		disable_mouse();
	} else {
		enable_mouse();
	}
}

void IWindow::enable_mouse() {
	m_mouse_enabled = true;
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void IWindow::disable_mouse() {
	m_mouse_enabled = false;
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
