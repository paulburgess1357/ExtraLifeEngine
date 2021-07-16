#pragma once
#include "../../Interfaces/Window/IWindow.h"
#include "../../Interfaces/Shader/IShaderProgram.h"
#include "FrameBufferType.h"
#include <memory>

class IFrameBuffer{
	
public:
	IFrameBuffer(const IWindow& window, IShaderProgram& shader_program);
	virtual ~IFrameBuffer() = default;

	static std::unique_ptr<IFrameBuffer> create_framebuffer(const IWindow& window, IShaderProgram& shader_program);

	virtual void bind() const = 0;
	virtual void unbind() const = 0;
	
	virtual void bind_framebuffer_texture() const = 0;
	virtual void unbind_framebuffer_texture() const = 0;

	virtual void bind_framebuffer_quad() const = 0;
	virtual void unbind_framebuffer_quad() const = 0;

	virtual void bind_framebuffer_shader() const;
	virtual void unbind_framebuffer_shader() const;

	virtual void clear_buffer() const = 0;
	virtual void destroy() const = 0;

	void initialize_framebuffer();
	void check_is_initialized() const;
	void update_scaling();
	void set_framebuffer_type(const FrameBufferType framebuffer_type);
	[[nodiscard]] FrameBufferType get_framebuffer_type() const;
	void set_framebuffer_shader(IShaderProgram* shader_program);
					
protected:
	void virtual create_texture_attachment() = 0;
	void virtual set_texture_format_by_type() = 0;
	void virtual attach_texture_buffer_by_type() = 0;
	void virtual rescale_texture_attachment() = 0;
	
	void virtual create_renderbuffer_attachment() = 0;
	void virtual set_renderbuffer_format_by_type() = 0;
	void virtual attach_renderbuffer_buffer_by_type() = 0;
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
	FrameBufferType m_framebuffer_type;

	bool m_is_initialized;

private:
	void virtual setup_quad() = 0;
	void virtual generate_fbo() = 0;
	
	IShaderProgram* m_shader_program;

};