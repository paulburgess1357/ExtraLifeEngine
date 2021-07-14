#pragma once
#include "../..//Interfaces/Window/IWindow.h"
#include "../../ResourceManagement/ShaderResource.h"
#include "../../Interfaces/Framebuffer/IFrameBuffer.h"
#include "entt/entity/registry.hpp"
#include <memory>

class FrameBufferHandler{

public:
	FrameBufferHandler(IWindow& window);
	~FrameBufferHandler() = default;
	
	void check_all_framebuffers_initialized() const;
	static bool gamma_correction_enabled();
	
private:
	void create_gamma_correction_buffer();
	
	ShaderResource m_standard_framebuffers_resource;
	IWindow& m_window;
	std::vector<std::unique_ptr<IFrameBuffer>> m_framebuffers;

	static bool m_gamma_correction_enabled;
	
};
