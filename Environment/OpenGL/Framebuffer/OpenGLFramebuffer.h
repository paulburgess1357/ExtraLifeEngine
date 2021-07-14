#pragma once
#include "../../Interfaces/Framebuffer/IFrameBuffer.h"

namespace OpenGL{

	class OpenGLFramebuffer : public IFrameBuffer {
		
	public:		
		OpenGLFramebuffer(const IWindow& window);
		~OpenGLFramebuffer() = default;

		void bind() const override;
		void unbind() const override;
		
		void bind_framebuffer_texture() const override;
		void unbind_framebuffer_texture() const override;

		void bind_framebuffer_quad() const override;
		void unbind_framebuffer_quad() const override;

		void clear_buffer() const override;
		void destroy() const override;
		
	private:
		void create_texture_attachment() override;
		void set_texture_format_by_type() override;
		void attach_texture_buffer_by_type() override;
		void rescale_texture_attachment() override;
		
		void create_renderbuffer_attachment() override;
		void set_renderbuffer_format_by_type() override;
		void attach_renderbuffer_buffer_by_type() override;
		void rescale_renderbuffer_attachment() override;
		
		void check_framebuffer_status() const override;
		void setup_quad() override;
		void generate_fbo() override;
		
	};
	
} // namespace OpenGL
