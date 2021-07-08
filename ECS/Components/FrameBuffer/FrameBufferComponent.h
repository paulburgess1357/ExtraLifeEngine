#pragma once
#include "../../Environment/Interfaces/Framebuffer/IFrameBuffer.h"

class FrameBufferComponent{
public:
	FrameBufferComponent(IFrameBuffer* frame_buffer)
		:m_frame_buffer{ frame_buffer }{		
	}	
	IFrameBuffer* m_frame_buffer = nullptr;
};