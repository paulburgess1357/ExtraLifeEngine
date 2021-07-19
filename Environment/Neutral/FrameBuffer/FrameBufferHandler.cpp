#include "FrameBufferHandler.h"
#include "../../Neutral/API/GraphicsAPI.h"
#include "../../../ECS/Components/FrameBuffer/FrameBufferComponent.h"
#include "../../../ECS/Components/Shader/ShaderComponent.h"
#include "../../../Utility/FatalError.h"
#include "../../../Utility/Print.h"
#include <glad/glad.h>

// Note: The framebuffer handler will disable the graphics api gamma correction
// if a FrameBufferType::GAMMA_CORRECTION or FrameBufferType::GAMMA_CORRECTION_W_HDR
// is active.  If that framebuffer is removed, it will reactivate the graphics
// api gamma correction.  You also cannot have both gamma correction framebuffers
// running at the same time.  If you attempt to load both, they will simply
// overwrite each other.

int FrameBufferHandler::m_execution_order = 0;
int FrameBufferHandler::m_gamma_priority = 9999999;
bool FrameBufferHandler::m_custom_framebuffer_gamma_enabled = false;

const std::map<int, IFrameBuffer*>& FrameBufferHandler::get_active_framebuffer_map() const{
	return m_active_framebuffers;
}

void FrameBufferHandler::load_framebuffer_shader(const std::string& shader_name, const std::string& vertex_shader_path, const std::string& fragment_shader_path){
	m_framebuffers_shader_resource.load(shader_name, vertex_shader_path, fragment_shader_path, false);
}

IShaderProgram* FrameBufferHandler::get_framebuffer_shader(const std::string& shader_name){
	return m_framebuffers_shader_resource.get(shader_name);
}

void FrameBufferHandler::load_framebuffer(const std::string& framebuffer_name, std::unique_ptr<IFrameBuffer> framebuffer){
	m_all_framebuffers[framebuffer_name] = std::move(framebuffer);
}

void FrameBufferHandler::move_framebuffer_to_active(const std::string& framebuffer_name){

	// Set execution order
	m_framebuffer_execution_order[framebuffer_name] = m_execution_order;

	// Add to active framebuffer map:
	IFrameBuffer* framebuffer_to_add = m_all_framebuffers[framebuffer_name].get();

	// If adding a gamma correction framebuffer, its priority of execution will be last.
	// Disable graphics api gamma correction.
	if(framebuffer_to_add->get_framebuffer_type() == FrameBufferType::GAMMA_CORRECTION || framebuffer_to_add->get_framebuffer_type() == FrameBufferType::GAMMA_CORRECTION_W_HDR){
		m_active_framebuffers[m_gamma_priority] = framebuffer_to_add;
		m_custom_framebuffer_gamma_enabled = true;
		disable_gamma_correction_graphics_api();
	} else{
		m_active_framebuffers[m_execution_order] = framebuffer_to_add;
		m_execution_order++;
	}
	
	// Ensure we aren't incorrectly adding too many framebuffers
	check_execution_count();
}

void FrameBufferHandler::move_framebuffer_to_inactive(const std::string& framebuffer_name){

	// Get execution number for active framebuffer
	const int framebuffer_execution_order = m_framebuffer_execution_order[framebuffer_name];
	
	// Remove from active framebuffers
	m_active_framebuffers.erase(framebuffer_execution_order);

	// If removing the gamma framebuffer, reactivate graphics api gamma correction.
	// We can identify the gamma correction framebuffer by its execution location
	if (framebuffer_execution_order == m_gamma_priority) {
		m_custom_framebuffer_gamma_enabled = false;
		enable_gamma_correction_graphics_api();
	}
		

	// Note: We don't alter the static execution order variable here. The reason
	// is because we may be removing a framebuffer in the middle.  E.g.:
	// Current active framebuffers:
	// 1 - framebuffer1
	// 2 - framebuffer2
	// 3 - framebuffer3
	// move 2 to inactive:
	// 1 - framebuffer1
	// 3 - framebuffer3
	// add new framebuffer to run (4)
	// 1 - framebuffer1
	// 3 - framebuffer3
	// 4 - framebuffer4
	// add framebuffer2 back to active
	// 1 - framebuffer1
	// 3 - framebuffer3
	// 4 - framebuffer4
	// 5 - framebuffer2
}

void FrameBufferHandler::load_framebuffer_and_move_to_active(const std::string& framebuffer_name, std::unique_ptr<IFrameBuffer> framebuffer){
	load_framebuffer(framebuffer_name, std::move(framebuffer));
	move_framebuffer_to_active(framebuffer_name);
}

bool FrameBufferHandler::gamma_correction_enabled() {
	return m_custom_framebuffer_gamma_enabled;
}

void FrameBufferHandler::check_all_framebuffers_initialized() const{
	for(const auto& framebuffer : m_all_framebuffers){
		framebuffer.second->check_is_initialized();
	}
}

void FrameBufferHandler::destroy(){
	for(const auto& framebuffer : m_all_framebuffers){
		Print::print("Destroying FrameBuffer: " + framebuffer.first);
		framebuffer.second->destroy();
	}
}

void FrameBufferHandler::check_execution_count() {
	if(m_execution_order > 99){
		FatalError::fatal_error("You are attempting to execute more than 99 framebuffers! Are you accidentally looping the adding of framebuffers?");
	}
}

void FrameBufferHandler::enable_gamma_correction_graphics_api() {

	Print::print("\nEnabling graphics api gamma correction");
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		glEnable(GL_FRAMEBUFFER_SRGB);
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan gamma correction check does  exist!.");
	} else {
		FatalError::fatal_error("Unknown graphics API type.  Unable to perform gamma correction check.");
	}
}

void FrameBufferHandler::disable_gamma_correction_graphics_api() {

	Print::print("\nDisabling graphics api gamma correction");
	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		glDisable(GL_FRAMEBUFFER_SRGB);
	} else if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan gamma correction check does  exist!.");
	} else {
		FatalError::fatal_error("Unknown graphics API type.  Unable to perform gamma correction check.");
	}

}
