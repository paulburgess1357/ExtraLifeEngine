#pragma once
#include "../../Interfaces/Window/IWindow.h"

namespace OpenGL{

	class OpenGLWindow : public IWindow {
		
	public:
		OpenGLWindow(const int window_width, const int window_height, const bool is_resizeable, const bool mouse_enabled, GLFWwindow* window);
		~OpenGLWindow() = default;		
		void swap_buffer() const override;
		void clear_color() const override;
		static void init_frame_buffer_callback();
		
	private:
		static void frame_buffer_callback(GLFWwindow* window, const int width, const int height);		
	};
	
} // namespace OpenGL


