#include "IFrameBuffer.h"
#include "../../Utility/FatalError.h"
#include "../../Neutral/API/GraphicsAPI.h"
#include "../../ResourceManagement/GraphicsConstants.h"
#include "../../OpenGL/Framebuffer/OpenGLFramebuffer.h"

IFrameBuffer::IFrameBuffer(const IWindow& window)
	:m_framebuffer_handle(GraphicsConstants::UNINITIALIZED_VALUE),
	 m_framebuffer_texture_handle(GraphicsConstants::UNINITIALIZED_VALUE),
	 m_framebuffer_renderbuffer_handle(GraphicsConstants::UNINITIALIZED_VALUE),
	 m_framebuffer_quad_vbo(GraphicsConstants::UNINITIALIZED_VALUE),
	 m_framebuffer_quad_vao(GraphicsConstants::UNINITIALIZED_VALUE),
	 m_window{ window }{
}

unsigned int IFrameBuffer::get_framebuffer_handle() const{
	return m_framebuffer_handle;
}

unsigned int IFrameBuffer::get_framebuffer_renderbuffer_handle() const{
	return m_framebuffer_renderbuffer_handle;
}

unsigned int IFrameBuffer::get_framebuffer_quad_vbo() const{
	return m_framebuffer_quad_vbo;
}

unsigned int IFrameBuffer::get_framebuffer_quad_vao() const{
	return m_framebuffer_quad_vao;
}

void IFrameBuffer::initialize(){
	// Bind the framebuffer
	bind();

	// Texture image that we attach as a color attachment: 
	create_texture_attachment();
	attach_texture_attachment_to_framebuffer();

	// We need to do depth and stencil testing, so we add a depth and stencil
	// attachment
	create_renderbuffer_attachment();
	attach_renderbuffer_attachment_to_framebuffer();

	// Check framebuffer for necessary attachments
	check_framebuffer_status();

	// Unbind framebuffer:
	unbind();
}

std::unique_ptr<IFrameBuffer> IFrameBuffer::create_framebuffer(const IWindow& window) {
	std::unique_ptr<IFrameBuffer> frame_buffer{ nullptr };

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		frame_buffer = std::make_unique<OpenGL::OpenGLFramebuffer>(window);
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan framebuffer does not exist!.");
	} else {
		FatalError::fatal_error("Unknown graphics API type.  Cannot return framebuffer.");
	}

	frame_buffer->initialize();
	return frame_buffer;
}
