#pragma once
#include "entt/entity/registry.hpp"
#include <memory>

class IFrameBufferRenderer{
	
public:
	virtual ~IFrameBufferRenderer() = default;
	virtual void start_render(entt::registry & registry) const = 0;
	virtual void end_render(entt::registry& registry) const = 0;
	static std::unique_ptr<IFrameBufferRenderer> get_framebuffer_renderer();
};