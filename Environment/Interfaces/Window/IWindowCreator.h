#pragma once
#include "../../Interfaces//Window/IWindow.h"
#include <memory>

class IWindowCreator {
	
public:	
	IWindowCreator();	
	virtual ~IWindowCreator() = default;
	[[nodiscard]] virtual std::shared_ptr<IWindow> create_glfw_window() = 0;
	[[nodiscard]] static std::shared_ptr<IWindow> create_window(const int width, const int height, const bool mouse_enabled, const bool is_resizeable);
	
protected:
	static void init_glfw();
	void init_glfw_window(const int width, const int height);	
	void init_glfw_input() const;
	void init_callbacks() const;
	static void init_vsync();

	GLFWwindow* m_window;
	
};

