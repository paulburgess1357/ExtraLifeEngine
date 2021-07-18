#pragma once
#include "../../ResourceManagement/ShaderResource.h"
#include "../../Interfaces/Framebuffer/IFrameBuffer.h"
#include "entt/entity/registry.hpp"
#include <map>

class FrameBufferHandler{

public:
	FrameBufferHandler() = default;
	~FrameBufferHandler() = default;
	
	[[nodiscard]] const std::map<int, IFrameBuffer*>& get_active_framebuffer_map() const;
	void load_framebuffer_shader(const std::string& shader_name, const std::string& vertex_shader_path, const std::string& fragment_shader_path);
	IShaderProgram* get_framebuffer_shader(const std::string& shader_name);

	void load_framebuffer(const std::string& framebuffer_name, std::unique_ptr<IFrameBuffer> framebuffer);
	void move_framebuffer_to_active(const std::string& framebuffer_name);
	void load_framebuffer_and_move_to_active(const std::string& framebuffer_name, std::unique_ptr<IFrameBuffer> framebuffer);
	void move_framebuffer_to_inactive(const std::string& framebuffer_name);

	void check_all_framebuffers_initialized() const;
	static bool gamma_correction_enabled();	
	void destroy();
	
private:
	ShaderResource m_framebuffers_shader_resource;

	// Framebuffer vector will run in the order they are inserted.  The one
	// exception to this is if a gamma framebuffer exists.  If the gamma
	// framebuffer exists, it will run last and apply gamma correction to
	// everything that has run.  The gamma correction framebuffer is NOT
	// in the active framebuffers

	// Only active framebuffers will run
	std::map<int, IFrameBuffer*> m_active_framebuffers;

	// All framebuffers stored (allows quick swapping of framebuffers)
	std::map<std::string, std::unique_ptr<IFrameBuffer>> m_all_framebuffers;
	std::map<std::string, int> m_framebuffer_execution_order;
	static int m_execution_order;
	static void check_execution_count();
	
	// If a gamma framebuffer is added this is set to true
	static int m_gamma_priority;
	static bool m_gamma_enabled;
	
};
