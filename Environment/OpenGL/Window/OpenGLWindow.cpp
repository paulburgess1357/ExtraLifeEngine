#include "OpenGLWindow.h"
#include <glad/glad.h>

OpenGL::OpenGLWindow::OpenGLWindow(const int window_width, const int window_height, const bool is_resizeable, const bool mouse_enabled, GLFWwindow* window)
	:IWindow{ window_width, window_height, is_resizeable, mouse_enabled, window } {
}

void OpenGL::OpenGLWindow::swap_buffer() const {
	glfwSwapBuffers(m_window);
}

void OpenGL::OpenGLWindow::clear_color() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGL::OpenGLWindow::init_frame_buffer_callback() {
	glfwSetFramebufferSizeCallback(m_window, frame_buffer_callback);
}

void OpenGL::OpenGLWindow::frame_buffer_callback(GLFWwindow* window, const int width, const int height) {
	m_width = width;
	m_height = height;
	glViewport(0, 0, width, height);
}