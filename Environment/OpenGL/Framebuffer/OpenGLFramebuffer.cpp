#include "OpenGLFramebuffer.h"
#include "../../Utility/FatalError.h"
#include <glad/glad.h>

#include "../../../Utility/Print.h"

// Framebuffer requirements
// 1) One Buffer: Color, Depth, or Stencil
// 2) At least one color attachment
// 3) All attachments should be complete (reserved memory)
// 4) Each buffer should have the same number of samples

// Attachments
// Two Options: Textures or Renderbuffer Objects
// Textures: All rendering commands write to the texture
// Renderbuffer: Faster than texture due to no conversions.  Data is stored
//               directly into the buffer
//               Write only: Often used for depth and stencil attachments

// learnopengl.com: 
// The general rule is that if you never need to sample data from a specific
// buffer, it is wise to use a renderbuffer object for that specific buffer.
// If you need to sample data from a specific buffer like colors or depth
// values, you should use a texture attachment instead.

// To draw the scene to a single texture:
// 1) Render the scene like normal with the new framebuffer bound
// 2) Bind to the default framebuffer
// 3) Draw a quad that spans the entire screen with the new framebuffer's color
//    buffer as its texture

OpenGL::OpenGLFramebuffer::OpenGLFramebuffer(const IWindow& window)
	:IFrameBuffer{ window } {
}

void OpenGL::OpenGLFramebuffer::setup_quad() {

	float quad_vertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenBuffers(1, &m_framebuffer_quad_vbo);
	glGenVertexArrays(1, &m_framebuffer_quad_vao);
	
	glBindVertexArray(m_framebuffer_quad_vao);

	// Store Data
	glBindBuffer(GL_ARRAY_BUFFER, m_framebuffer_quad_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);

	// Vertex Position Data
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Vertex Texture Data
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void OpenGL::OpenGLFramebuffer::generate_fbo() {
	glGenFramebuffers(1, &m_framebuffer_handle);
}

void OpenGL::OpenGLFramebuffer::bind() const{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer_handle);
}

void OpenGL::OpenGLFramebuffer::unbind() const {
	// Will revert to the default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGL::OpenGLFramebuffer::bind_framebuffer_texture() const{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_framebuffer_texture_handle);
}

void OpenGL::OpenGLFramebuffer::unbind_framebuffer_texture() const{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGL::OpenGLFramebuffer::bind_framebuffer_quad() const {
	glBindVertexArray(m_framebuffer_quad_vao);
}

void OpenGL::OpenGLFramebuffer::unbind_framebuffer_quad() const {
	glBindVertexArray(0);
}

void OpenGL::OpenGLFramebuffer::clear_buffer() const{
	// Clear the custom bound (this class) framebuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGL::OpenGLFramebuffer::destroy() const{
	if(m_is_initialized){
		Print::print("Destroying Framebuffer");
		glDeleteFramebuffers(1, &m_framebuffer_handle);
		glDeleteTextures(1, &m_framebuffer_texture_handle);
		glDeleteRenderbuffers(1, &m_framebuffer_renderbuffer_handle);
		glDeleteBuffers(1, &m_framebuffer_quad_vbo);
		glDeleteVertexArrays(1, &m_framebuffer_quad_vao);
	}
}

void OpenGL::OpenGLFramebuffer::create_texture_attachment() {
	
	glGenTextures(1, &m_framebuffer_texture_handle);
	glBindTexture(GL_TEXTURE_2D, m_framebuffer_texture_handle);

	set_texture_format_by_type();
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	attach_texture_buffer_by_type();
}

void OpenGL::OpenGLFramebuffer::set_texture_format_by_type(){
	switch (m_framebuffer_type) {
		case FrameBufferType::STANDARD:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_window_width, m_window_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			break;
		case FrameBufferType::FLOATING_POINT:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_window_width, m_window_height, 0, GL_RGBA, GL_FLOAT, NULL);
			break;
		default:
			FatalError::fatal_error("Unknown framebuffer type for creating texture attachment in OpenGLFrameBuffer::create_texture_attachment()");
		}
}

void OpenGL::OpenGLFramebuffer::attach_texture_buffer_by_type(){
	// Standard and Floating Point are identical for texture:
	switch (m_framebuffer_type) {
		case FrameBufferType::STANDARD:
		case FrameBufferType::FLOATING_POINT:
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_framebuffer_texture_handle, 0);
			break;
		default:
			FatalError::fatal_error("Unknown framebuffer type for attaching texture buffer in OpenGLFrameBuffer::create_texture_attachment()");
	}
}

void OpenGL::OpenGLFramebuffer::rescale_texture_attachment(){
	
	glBindTexture(GL_TEXTURE_2D, m_framebuffer_texture_handle);
	set_texture_format_by_type();
	glBindTexture(GL_TEXTURE_2D, 0);
	attach_texture_buffer_by_type();
}

void OpenGL::OpenGLFramebuffer::create_renderbuffer_attachment(){
	
	glGenRenderbuffers(1, &m_framebuffer_renderbuffer_handle);
	glBindRenderbuffer(GL_RENDERBUFFER, m_framebuffer_renderbuffer_handle);

	// Render buffers are write only.  They are often used for depth or stencil
	// testing.  This creates a depth AND stencil renderbuffer object:
	set_renderbuffer_format_by_type();
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	attach_renderbuffer_buffer_by_type();
	
}

void OpenGL::OpenGLFramebuffer::set_renderbuffer_format_by_type(){
	switch(m_framebuffer_type){
		case FrameBufferType::STANDARD:
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_window_width, m_window_height);
			break;
		case FrameBufferType::FLOATING_POINT:
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_window_width, m_window_height);
			break;
		default:
			FatalError::fatal_error("Unknown framebuffer type for creating renderbuffer attachment in OpenGLFrameBuffer::create_renderbuffer_attachment()");
		}
}

void OpenGL::OpenGLFramebuffer::attach_renderbuffer_buffer_by_type(){
	switch (m_framebuffer_type) {
		case FrameBufferType::STANDARD:
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_framebuffer_renderbuffer_handle);
			break;
		case FrameBufferType::FLOATING_POINT:
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_framebuffer_renderbuffer_handle);
			break;
		default:
			FatalError::fatal_error("Unknown framebuffer type for attaching texture buffer in OpenGLFrameBuffer::create_texture_attachment()");
		}
}


void OpenGL::OpenGLFramebuffer::rescale_renderbuffer_attachment(){
	
	glBindRenderbuffer(GL_RENDERBUFFER, m_framebuffer_renderbuffer_handle);
	set_renderbuffer_format_by_type();
	
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	attach_renderbuffer_buffer_by_type();
}

void OpenGL::OpenGLFramebuffer::check_framebuffer_status() const{
	const GLenum framebuffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(framebuffer_status != GL_FRAMEBUFFER_COMPLETE){
		std::string error;
		switch(framebuffer_status){
		case GL_FRAMEBUFFER_UNDEFINED:
			error = "GL_FRAMEBUFFER_UNDEFINED";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			error = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			error = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			error = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			error = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			error = "GL_FRAMEBUFFER_UNSUPPORTED";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			error = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			error = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS ";
			break;
		default: 
			error = "Unknown Framebuffer Error!";
			break;			
		}
		FatalError::fatal_error("Framebuffer error: " + error);				
	}
}
