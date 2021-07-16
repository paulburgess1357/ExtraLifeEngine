#include "IFrameBufferRenderer.h"
#include "../OpenGL/OpenGLFrameBufferRenderer.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"
#include "../../../../Utility/FatalError.h"

IFrameBufferRenderer::IFrameBufferRenderer(FrameBufferHandler& framebuffer_handler)
	:m_framebuffer_handler{ framebuffer_handler }{
}


std::unique_ptr<IFrameBufferRenderer> IFrameBufferRenderer::get_framebuffer_renderer(){

	std::unique_ptr<IFrameBufferRenderer> renderer{ nullptr };

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		renderer = std::make_unique<OpenGL::OpenGLFrameBufferRenderer>();
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan framebuffer renderer does not exist!.");
	} else {
		FatalError::fatal_error("Unknown Graphics API Type.  Cannot return framebuffer renderer.");
	}

	return renderer;
	
}
