#pragma once
#include "FrameBufferHandler.h"

class FrameBufferLoader{
	
public:
	FrameBufferLoader(IWindow& window, FrameBufferHandler& framebuffer_handler);
	~FrameBufferLoader() = default;

	void load_framebuffers() const;
	
private:
	void load_gamma_correction() const;
	void load_edge_detection() const;
	void load_blur() const;
	
	IWindow& m_window;
	FrameBufferHandler& m_framebuffer_handler;
};
