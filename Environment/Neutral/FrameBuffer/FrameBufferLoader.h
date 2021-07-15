#pragma once
#include "FrameBufferHandler.h"

class FrameBufferLoader{
	
public:
	FrameBufferLoader(FrameBufferHandler& framebuffer_handler, IWindow& window);
	~FrameBufferLoader() = default;

	void load_gamma_correction() const;
	
private:
	FrameBufferHandler& m_framebuffer_handler;
	IWindow& m_window;
};