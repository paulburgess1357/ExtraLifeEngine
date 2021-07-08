#pragma once
#include "../Interfaces/IFrameBufferRenderer.h"

namespace OpenGL{

	class OpenGLFrameBufferRenderer : public IFrameBufferRenderer{
	public:
		void start_render(entt::registry& registry) const override;
		void end_render(entt::registry& registry) const override;
	};
	
} // namespace OpenGL