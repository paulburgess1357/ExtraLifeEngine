#include <glad/glad.h>
#include "OpenGLStentilTesting.h"

void OpenGL::OpenGLStencilTesting::start_stencil_settings() const{

	// Stencil buffer should be cleared (window clear buffer should be clearing
	// the stencil buffer at the start of each loop)
	// TODO write clear buffer for stencil class? That way I only have to
	// TODO clear the stencil buffer when the stencil class is used?
	// TODO I think it owuld have to be cleared in both the normal stencil buffer
	// TODO and framebuffer... Yes this is true.  The framebuffer I have already
	// TODO clears its own stencil buffer. This should just be the clear command
	// TODO for the standard normal stencil buffer,.
	
	// 1 Action to take if stencil test fails
	// 2 Action to take if stencil test passes but depth test fails
	// 3 Action to take if stencil test fails and depth test fails
	// GL_KEEP: The current stencil value is kept
	// GL_REPLACE: Value is replaced with stencil value in: glStencilFunc
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);



	
}

void OpenGL::OpenGLStencilTesting::end_stencil_settings() const{
	
}

void OpenGL::OpenGLStencilTesting::clear_buffer() const{
	
}

void OpenGL::OpenGLStencilTesting::destroy() const{
	
}