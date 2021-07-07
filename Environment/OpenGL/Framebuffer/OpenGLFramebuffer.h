#pragma once
#include "../../Interfaces/Framebuffer/IFrameBuffer.h"

namespace OpenGL{

	class OpenGLFramebuffer : public IFrameBuffer {
		
	public:		
		OpenGLFramebuffer(const IWindow& window);
		~OpenGLFramebuffer() = default;

		void setup_quad();
		void bind() const override;
		void bind_framebuffer_texture() const override;
		void unbind_framebuffer_texture() const override;
		void unbind() const override;
		void destroy() const override;

		void create_texture_attachment() override;
		void attach_texture_attachment_to_framebuffer() const override;
		//TODO create update_texture_attachment function to handle screen size changing

		void create_renderbuffer_attachment() override;
		void attach_renderbuffer_attachment_to_framebuffer() const override;

		void check_framebuffer_status() const override;
		
	private:	
		void generate_fbo();
		
	};
	
} // namespace OpenGL