#include "WindowFactory.h"
#include "../../Utility/Print.h"
#include "../../Environment/Interfaces/Window/IWindowCreator.h"
#include "../../Environment/OpenGL/Window/OpenGLWindowCreator.h"

std::shared_ptr<Window> WindowFactory::create_opengl_window(const int width, const int height, const bool is_resizeable){
	std::unique_ptr<IWindowCreator> window_creator = std::make_unique<OpenGL::OpenGLWindowCreator>(width, height, is_resizeable);
	return window_creator->create_window();	
}

void WindowFactory::create_vulkan_window(){
	Print::print("This method doesn't exist yet!");
}
