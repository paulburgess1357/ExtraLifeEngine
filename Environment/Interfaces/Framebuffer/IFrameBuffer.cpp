#include "IFrameBuffer.h"
#include "../../Utility/FatalError.h"
#include "../../Neutral/API/GraphicsAPI.h"
#include "../../ResourceManagement/GraphicsConstants.h"
#include "../../OpenGL/Framebuffer/OpenGLFramebuffer.h"
#include "../../../Utility/Print.h"

IFrameBuffer::IFrameBuffer(const IWindow& window)
	:m_framebuffer_handle(GraphicsConstants::UNINITIALIZED_VALUE),
	 m_framebuffer_texture_handle(GraphicsConstants::UNINITIALIZED_VALUE),
	 m_framebuffer_renderbuffer_handle(GraphicsConstants::UNINITIALIZED_VALUE),
	 m_framebuffer_quad_vbo(GraphicsConstants::UNINITIALIZED_VALUE),
	 m_framebuffer_quad_vao(GraphicsConstants::UNINITIALIZED_VALUE),
	 m_window{ window },
	 m_window_width{ m_window.get_width() },
	 m_window_height{ m_window.get_height() }{
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

bool IFrameBuffer::window_size_has_changed() const{
	return m_window_width != m_window.get_width() || m_window_height != m_window.get_height();
}

void IFrameBuffer::update_window_size(){
	m_window_width = m_window.get_width();
	m_window_height = m_window.get_height();
}

void IFrameBuffer::update_scaling(){
	if(window_size_has_changed()){
		Print::print("Rescaling Framebuffer");
		bind();
		update_window_size();
		rescale_texture_attachment();
		rescale_renderbuffer_attachment();
		unbind();
	}
}

void IFrameBuffer::initialize(){

	// Bind the framebuffer
	bind();

	// Texture image that we attach as a color attachment: 
	create_texture_attachment();

	// We need to do depth and stencil testing, so we add a depth and stencil
	// attachment
	create_renderbuffer_attachment();

	// Check framebuffer for necessary attachments
	check_framebuffer_status();

	// Unbind framebuffer:
	unbind();
}
