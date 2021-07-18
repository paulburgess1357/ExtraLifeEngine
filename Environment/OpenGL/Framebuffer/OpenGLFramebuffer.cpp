#include "OpenGLFramebuffer.h"
#include "../../Utility/FatalError.h"
#include "../../../Utility/Print.h"
#include <glad/glad.h>

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

// Texture attachment vs render buffer (learnopengl.com): 
// The general rule is that if you never need to sample data from a specific
// buffer, it is wise to use a renderbuffer object for that specific buffer.
// If you need to sample data from a specific buffer like colors or depth
// values, you should use a texture attachment instead.

// ***** Renderbuffer w/ other attachments *****
// Texture attachments are set to use a single color buffer
// Renderbuffer attachments are set to use the depth buffer
// Nothing is using the stencil buffer.  If you plan on using the stencil
// buffer you will have to update a few things:
//  - glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_framebuffer_renderbuffer_handle);
//  - glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_window_width, m_window_height);
//  - clear_buffer() will have to be updated to clear the stencil buffer

// Gamma Correction
// https://gamedev.net/forums/topic/697254-gamma-correction-confusion/5381563/

OpenGL::OpenGLFramebuffer::OpenGLFramebuffer(const IWindow& window, IShaderProgram& shader_program)
	:IFrameBuffer{ window, shader_program } {
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

void OpenGL::OpenGLFramebuffer::bind_framebuffer_shader() const{
	m_shader_program->bind();
}

void OpenGL::OpenGLFramebuffer::unbind_framebuffer_shader() const{
	m_shader_program->unbind();
}

void OpenGL::OpenGLFramebuffer::clear_buffer() const{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		case FrameBufferType::GAMMA_CORRECTION:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_window_width, m_window_height, 0, GL_RGBA, GL_FLOAT, NULL);
			// GL_SRGB8_ALPHA8 would work for gamma correction
			// However, I am using GL_RGBA16F to account for future HDR correction
			// E.g. HDR FrameBuffer -> Gamma FrameBuffer -> Output (So the same precision is necessary)
			break;
		default:
			FatalError::fatal_error("Unknown framebuffer type for creating texture attachment in OpenGLFrameBuffer::create_texture_attachment()");
		}
}

void OpenGL::OpenGLFramebuffer::attach_texture_buffer_by_type(){
	switch (m_framebuffer_type) {
		case FrameBufferType::STANDARD:
		case FrameBufferType::FLOATING_POINT:
		case FrameBufferType::GAMMA_CORRECTION:
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
	set_renderbuffer_format_by_type();
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	attach_renderbuffer_buffer_by_type();
}

void OpenGL::OpenGLFramebuffer::set_renderbuffer_format_by_type(){
	switch(m_framebuffer_type){
		case FrameBufferType::STANDARD:
		case FrameBufferType::FLOATING_POINT:
		case FrameBufferType::GAMMA_CORRECTION:
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_window_width, m_window_height);
			break;
		default:
			FatalError::fatal_error("Unknown framebuffer type for creating renderbuffer attachment in OpenGLFrameBuffer::create_renderbuffer_attachment()");
		}
}

void OpenGL::OpenGLFramebuffer::attach_renderbuffer_buffer_by_type(){
	switch (m_framebuffer_type) {
		case FrameBufferType::STANDARD:
		case FrameBufferType::FLOATING_POINT:
		case FrameBufferType::GAMMA_CORRECTION:
			// This must be in line with the set_renderbuffer_format_by_type() function (attachment version not component version)
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
