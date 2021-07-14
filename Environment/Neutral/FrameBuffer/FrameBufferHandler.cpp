#include "FrameBufferHandler.h"
#include "../../../ECS/Components/FrameBuffer/FrameBufferComponent.h"
#include "../../../ECS/Components/Shader/ShaderComponent.h"

bool FrameBufferHandler::m_gamma_correction_enabled = false;

FrameBufferHandler::FrameBufferHandler(IWindow& window)
	:m_window{ window }{
	create_gamma_correction_buffer();
}

void FrameBufferHandler::create_gamma_correction_buffer(){

	std::unique_ptr<IFrameBuffer> gamma_framebuffer = IFrameBuffer::create_framebuffer(m_window);
	gamma_framebuffer->set_framebuffer_type(FrameBufferType::GAMMA_CORRECTION);
	gamma_framebuffer->initialize_framebuffer();
	
	m_standard_framebuffers_resource.load("framebuffer_gamma_shader", "Assets/shaders/framebuffer_shaders/framebuffer_vertex.glsl", "Assets/shaders/framebuffer_shaders/framebuffer_fragment_gamma_correction.glsl", false);
	IShaderProgram* shader_program = m_standard_framebuffers_resource.get("framebuffer_gamma_shader");

	// Binding the sampler2d screen_quad to tex unit 0 (framebuffer only has one texture)
	shader_program->set_uniform("screen_quad", 0);

	// Set shader program
	gamma_framebuffer->set_framebuffer_shader(shader_program);

	// QC check (also done in game manager in case its forgotten here)
	gamma_framebuffer->check_is_initialized();

	// Set gamma correction (impacts how non-lighting textures are loaded)
	m_gamma_correction_enabled = true;
}

void FrameBufferHandler::check_all_framebuffers_initialized() const{
	for(const auto& framebuffer : m_framebuffers){
		framebuffer->check_is_initialized();
	}
}

bool FrameBufferHandler::gamma_correction_enabled(){
	return m_gamma_correction_enabled;
}
