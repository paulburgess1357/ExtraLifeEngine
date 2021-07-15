#include "FrameBufferLoader.h"

FrameBufferLoader::FrameBufferLoader(FrameBufferHandler& framebuffer_handler, IWindow& window)
	:m_framebuffer_handler{ framebuffer_handler },
	m_window{ window }{
}

void FrameBufferLoader::load_gamma_correction() const{
	std::unique_ptr<IFrameBuffer> gamma_framebuffer = IFrameBuffer::create_framebuffer(m_window);
	gamma_framebuffer->set_framebuffer_type(FrameBufferType::GAMMA_CORRECTION);
	gamma_framebuffer->initialize_framebuffer();

	m_framebuffer_handler.load_framebuffer_shader("framebuffer_gamma_shader", "Assets/shaders/framebuffer_shaders/framebuffer_vertex.glsl", "Assets/shaders/framebuffer_shaders/framebuffer_fragment_gamma_correction.glsl");
	IShaderProgram* shader_program = m_framebuffer_handler.get_framebuffer_shader("framebuffer_gamma_shader");

	// Binding the sampler2d screen_quad to tex unit 0 (framebuffer only has one texture)
	shader_program->set_uniform("screen_quad", 0);

	// Set shader program
	gamma_framebuffer->set_framebuffer_shader(shader_program);

	// QC check (also done in game manager in case its forgotten here)
	gamma_framebuffer->check_is_initialized();

	// Load into framebuffer handler (and gamma correction buffer)
	m_framebuffer_handler.load_framebuffer("gamma_correction", std::move(gamma_framebuffer));

	// Any other framebuffer will be activated with the following line:
	// m_framebuffer_handler.move_framebuffer_to_active("gamma_correction");
	// However, since this is the gamma framebuffer:		
	FrameBufferHandler::set_gamma_correction_buffer(gamma_framebuffer.get());

}
