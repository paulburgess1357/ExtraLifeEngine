#pragma once
#include "Window.h"
#include <memory>

class WindowFactory{
	
public:
	static std::shared_ptr<Window> create_opengl_window(const int width, const int height, const bool is_resizeable);
	static void create_vulkan_window();
	
};

