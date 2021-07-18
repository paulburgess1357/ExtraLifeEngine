#pragma once
#include "../../Environment/Neutral/FrameBuffer/FrameBufferHandler.h"
#include <memory>

class IFrameBufferRenderer{
	
public:
	IFrameBufferRenderer(FrameBufferHandler& framebuffer_handler);
	virtual ~IFrameBufferRenderer() = default;
	virtual void start_render() = 0;
	virtual void end_render() = 0;
	static std::unique_ptr<IFrameBufferRenderer> get_framebuffer_renderer(FrameBufferHandler& framebuffer_handler);

protected:
	FrameBufferHandler& m_framebuffer_handler;
};
