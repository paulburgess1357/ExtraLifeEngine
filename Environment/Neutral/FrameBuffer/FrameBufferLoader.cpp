#include "FrameBufferLoader.h"

FrameBufferLoader::FrameBufferLoader(IWindow& window, FrameBufferHandler& framebuffer_handler)
	:m_window{ window },
	m_framebuffer_handler{ framebuffer_handler }{
}

void FrameBufferLoader::load_framebuffers() const{
	load_gamma_correction();
}

void FrameBufferLoader::load_gamma_correction() const{

	m_framebuffer_handler.load_framebuffer_shader("framebuffer_gamma_shader", "Assets/shaders/framebuffer_shaders/framebuffer_vertex.glsl", "Assets/shaders/framebuffer_shaders/framebuffer_fragment_gamma_correction.glsl");
	IShaderProgram* shader_program = m_framebuffer_handler.get_framebuffer_shader("framebuffer_gamma_shader");
	
	std::unique_ptr<IFrameBuffer> gamma_framebuffer = IFrameBuffer::create_framebuffer(m_window, *shader_program);
	gamma_framebuffer->set_framebuffer_type(FrameBufferType::GAMMA_CORRECTION);
	gamma_framebuffer->initialize_framebuffer();

	// Binding the sampler2d screen_quad to tex unit 0 (framebuffer only has one texture)
	shader_program->set_uniform("screen_quad", 0);

	// Load into framebuffer handler and set active
	m_framebuffer_handler.load_framebuffer_and_move_to_active("gamma_correction", std::move(gamma_framebuffer));

}
