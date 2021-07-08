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
		void rescale_texture_attachment() override;
		
		void create_renderbuffer_attachment() override;
		void rescale_renderbuffer_attachment() override;
		
		void check_framebuffer_status() const override;
		void setup_quad();
		void generate_fbo();
		
	};
	
} // namespace OpenGL
