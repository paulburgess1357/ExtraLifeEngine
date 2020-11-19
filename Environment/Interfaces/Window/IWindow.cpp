#include "IWindow.h"

int IWindow::m_width{ 0 };
int IWindow::m_height{ 0 };
bool IWindow::m_is_resizeable{ true };
GLFWwindow* IWindow::m_window{ nullptr };

IWindow::IWindow(const int width, const int height, const bool is_resizeable, GLFWwindow* window){
	m_width = width;
	m_height = height;
	m_is_resizeable = is_resizeable;
	m_window = window;
}

IWindow::~IWindow() {
	glfwDestroyWindow(m_window);
}

GLFWwindow* IWindow::get_glfw_ptr() {
	return m_window;
}

int IWindow::get_width(){
	return m_width;
}

int IWindow::get_height(){
	return m_height;
}

bool IWindow::is_resizeable(){
	return m_is_resizeable;
}
