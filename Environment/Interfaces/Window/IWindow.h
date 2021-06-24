#pragma once
#include <GLFW/glfw3.h>

class IWindow{
	
public:	
	virtual ~IWindow();
	
	virtual void swap_buffer() const = 0;
	virtual void clear_color() const = 0;	
	virtual GLFWwindow* get_glfw_ptr();

	static int get_width();
	static int get_height();
	static bool is_resizeable();
	static void toggle_mouse();
	static bool get_mouse_enabled();

protected:
	IWindow(const int width, const int height, const bool is_resizeable, const bool mouse_enabled, GLFWwindow* window);
	static int m_width;
	static int m_height;
	static bool m_is_resizeable;
	static bool m_mouse_enabled;
	static GLFWwindow* m_window;

private:
	static void enable_mouse();
	static void disable_mouse();
	
};
