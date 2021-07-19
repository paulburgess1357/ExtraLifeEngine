#pragma once
#include "../Interfaces/IFrameBufferRenderer.h"

namespace OpenGL{

	class OpenGLFrameBufferRenderer : public IFrameBufferRenderer{
	public:
		OpenGLFrameBufferRenderer(FrameBufferHandler& framebuffer_handler);
		void start_render() override;
		void end_render() override;
	};
	
} // namespace OpenGL
