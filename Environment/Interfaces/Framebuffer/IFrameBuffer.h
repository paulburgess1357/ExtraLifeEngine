#pragma once
#include "../../Interfaces/Window/IWindow.h"
#include <memory>

class IFrameBuffer{
public:
	IFrameBuffer(const IWindow& window);
	virtual ~IFrameBuffer() = default;
	virtual void bind() const = 0;
	virtual void unbind() const = 0;
	virtual void destroy() const = 0;

	[[nodiscard]] unsigned int get_framebuffer_handle() const;
	[[nodiscard]] unsigned int get_framebuffer_texture_handle() const;
	[[nodiscard]] unsigned int get_framebuffer_renderbuffer_handle() const;

	[[nodiscard]] unsigned int get_framebuffer_quad_vbo() const;
	[[nodiscard]] unsigned int get_framebuffer_quad_vao() const;

	static std::unique_ptr<IFrameBuffer> create_framebuffer(const IWindow& window);
	
	// Attachment types
	// Texture
	// TODO create update_texture_attachment function to handle screen size changing
	void virtual create_texture_attachment() = 0;
	void virtual attach_texture_attachment_to_framebuffer() const = 0;	

	// Renderbuffer
	// TODO create update_texture_attachment function to handle screen size changing
	void virtual create_renderbuffer_attachment() = 0;
	void virtual attach_renderbuffer_attachment_to_framebuffer() const = 0;
		
protected:	
	virtual void check_framebuffer_status() const = 0;
	
	unsigned int m_framebuffer_handle;
	unsigned int m_framebuffer_texture_handle;
	unsigned int m_framebuffer_renderbuffer_handle;

	unsigned int m_framebuffer_quad_vbo;
	unsigned int m_framebuffer_quad_vao;

	const IWindow& m_window;

private:
	void initialize();
};