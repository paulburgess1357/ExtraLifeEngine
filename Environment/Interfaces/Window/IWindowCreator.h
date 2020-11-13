#pragma once
#include "../../Neutral/Window/Window.h"
#include <memory>

class IWindowCreator {
	
public:	
	IWindowCreator();	
	virtual ~IWindowCreator() = default;
	[[nodiscard]] virtual std::shared_ptr<Window> create_window() = 0;
	
protected:
	static void init_glfw();
	void init_glfw_window(const int width, const int height);	
	void init_glfw_input() const;
	void init_callbacks() const;
	static void init_vsync();
	void center_mouse() const;

	GLFWwindow* m_window;
	
};

