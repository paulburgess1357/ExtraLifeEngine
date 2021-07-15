#include "FrameBufferHandler.h"
#include "../../../ECS/Components/FrameBuffer/FrameBufferComponent.h"
#include "../../../ECS/Components/Shader/ShaderComponent.h"
#include "../../../Utility/FatalError.h"
#include "../../../Utility/Print.h"

IFrameBuffer* FrameBufferHandler::m_gamma_framebuffer = nullptr;
int FrameBufferHandler::m_execution_order = 0;

FrameBufferHandler::FrameBufferHandler(IWindow& window)
	:m_window{ window }{
}

std::map<int, IFrameBuffer*> FrameBufferHandler::get_active_framebuffer_map() const{
	return m_active_framebuffers;
}

IFrameBuffer* FrameBufferHandler::get_gamma_framebuffer(){
	return m_gamma_framebuffer;
}


void FrameBufferHandler::load_framebuffer_shader(const std::string& shader_name, const std::string& vertex_shader_path, const std::string& fragment_shader_path){
	m_standard_framebuffers_resource.load(shader_name, vertex_shader_path, fragment_shader_path, false);
}

IShaderProgram* FrameBufferHandler::get_framebuffer_shader(const std::string& shader_name){
	return m_standard_framebuffers_resource.get(shader_name);
}

void FrameBufferHandler::load_framebuffer(const std::string& framebuffer_name, std::unique_ptr<IFrameBuffer> framebuffer){
	m_all_framebuffers[framebuffer_name] = std::move(framebuffer);
}

void FrameBufferHandler::move_framebuffer_to_active(const std::string& framebuffer_name){

	// Set execution order
	m_framebuffer_execution_order[framebuffer_name] = m_execution_order;

	// Add to active framebuffer map:
	m_active_framebuffers[m_execution_order] = m_all_framebuffers[framebuffer_name].get();

	// Increment execution order
	m_execution_order++;

	// Ensure we aren't incorrectly adding too many framebuffers
	check_execution_count();
}

void FrameBufferHandler::move_framebuffer_to_inactive(const std::string& framebuffer_name){

	// Get execution number for active framebuffer
	const unsigned int framebuffer_execution_order = m_framebuffer_execution_order[framebuffer_name];

	// Remove from active framebuffers	
	m_active_framebuffers.erase(framebuffer_execution_order);

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

void FrameBufferHandler::set_gamma_correction_buffer(IFrameBuffer* framebuffer){
	m_gamma_framebuffer = framebuffer;
}

bool FrameBufferHandler::gamma_correction_enabled() {
	return m_gamma_framebuffer != nullptr;
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
