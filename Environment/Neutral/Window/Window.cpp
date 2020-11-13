#include "Window.h"

int Window::m_width{ 0 };
int Window::m_height{ 0 };
bool Window::m_is_resizeable{ true };
GLFWwindow* Window::m_window{ nullptr };

Window::Window(const int width, const int height, const bool is_resizeable, GLFWwindow* window){
	m_width = width;
	m_height = height;
	m_is_resizeable = is_resizeable;
	m_window = window;
}

Window::~Window() {
	glfwDestroyWindow(m_window);
}

GLFWwindow* Window::get_glfw_ptr() {
	return m_window;
}

int Window::get_width(){
	return m_width;
}

int Window::get_height(){
	return m_height;
}

bool Window::is_resizeable(){
	return m_is_resizeable;
}