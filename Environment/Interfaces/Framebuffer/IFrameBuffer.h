#pragma once
#include "../../Interfaces/Window/IWindow.h"
#include <memory>

class IFrameBuffer{
	
public:
	IFrameBuffer(const IWindow& window);
	virtual ~IFrameBuffer() = default;
	static std::unique_ptr<IFrameBuffer> create_framebuffer(const IWindow& window);

	virtual void bind() const = 0;
	virtual void unbind() const = 0;
	
	virtual void bind_framebuffer_texture() const = 0;
	virtual void unbind_framebuffer_texture() const = 0;

	virtual void bind_framebuffer_quad() const = 0;
	virtual void unbind_framebuffer_quad() const = 0;

	virtual void clear_buffer() const = 0;
	virtual void destroy() const = 0;

	void update_scaling();
					
protected:
	void virtual create_texture_attachment() = 0;
	void virtual rescale_texture_attachment() = 0;
	
	void virtual create_renderbuffer_attachment() = 0;
	void virtual rescale_renderbuffer_attachment() = 0;
	
	virtual void check_framebuffer_status() const = 0;

	[[nodiscard]] bool window_size_has_changed() const;
	void update_window_size();
	
	unsigned int m_framebuffer_handle;
	unsigned int m_framebuffer_texture_handle;
	unsigned int m_framebuffer_renderbuffer_handle;

	unsigned int m_framebuffer_quad_vbo;
	unsigned int m_framebuffer_quad_vao;

	const IWindow& m_window;

	int m_window_width;
	int m_window_height;

private:
	void initialize();
	
};