#include "OpenGLWindowCreator.h"
#include "OpenGLWindow.h"
#include "../../Utility/Print.h"
#include <glad/glad.h>

std::shared_ptr<IWindow> OpenGL::OpenGLWindowCreator::m_opengl_window = nullptr;

OpenGL::OpenGLWindowCreator::OpenGLWindowCreator(const int width, const int height, const bool is_resizeable)
	:m_width { width },
	m_height { height },
	m_is_resizeable { is_resizeable }{
}

std::shared_ptr<IWindow> OpenGL::OpenGLWindowCreator::create_glfw_window() {

	if(m_opengl_window){
		return m_opengl_window;
	}
	
	init_glfw();
	init_glfw_hints();
	init_glfw_window(m_width, m_height);
	init_glad();
	init_opengl_settings();
	init_vsync();
	init_glfw_input();
	init_callbacks();

	if(!m_is_resizeable){
		center_mouse();
	}
	
	m_opengl_window = std::make_shared<OpenGLWindow>(m_width, m_height, m_is_resizeable, m_window);
	OpenGLWindow::init_frame_buffer_callback();	
	
	return m_opengl_window;
}

void OpenGL::OpenGLWindowCreator::init_glfw_hints() const {
	Print::print("Setting OpenGL OpenGLWindow Context");
	
	// OpenGL Settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// MSAA
	glfwWindowHint(GLFW_SAMPLES, 4);

	if (!m_is_resizeable) {
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}	
}

void OpenGL::OpenGLWindowCreator::init_glad() const {
	Print::print("Initializing GLAD");
	glfwMakeContextCurrent(m_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
	}
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

void OpenGL::OpenGLWindowCreator::init_opengl_settings() const {
	glViewport(0, 0, m_width, m_height);
	glClearColor(0.08f, 0.08f, 0.08f, 1.0f);

	// Depth Testing (requires glClear GL_DEPTH_BUFFER_BIT)
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Alpha blending
	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// MSAA
	glEnable(GL_MULTISAMPLE);

	// Face Culling
	// glEnable(GL_CULL_FACE);
	// Default enabled value(No need to specify unless winding order is not default)
	// glFrontFace(GL_CCW); 

	// Seamless Cubemap
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Polygon (line) mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
