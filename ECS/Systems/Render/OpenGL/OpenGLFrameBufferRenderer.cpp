#include "OpenGLFrameBufferRenderer.h"
#include "../../ECS/Components/FrameBuffer/FrameBufferComponent.h"
#include "../../ECS/Components/Shader/ShaderComponent.h"
#include <glad/glad.h>

// The framebuffer has two parts start_render and end_render
// E.g. : Cubemap render
//        Framebuffer start_render()
//        Other renderer render()
//        Other renderer render()
//        Framebuffer end_render()

void OpenGL::OpenGLFrameBufferRenderer::start_render(entt::registry& registry) const{

	auto view = registry.view<FrameBufferComponent, ShaderComponent>();

	for (auto entity : view) {
		auto& framebuffer_component = view.get<FrameBufferComponent>(entity);

		framebuffer_component.m_frame_buffer->bind();

		// Depth testing necessary (normally disabled for on-screen quad)
		glEnable(GL_DEPTH_TEST); //TODO NOTE may have to ensure that the cubemap renderer happens 1st, then framebuffer, then other renderers, then framebuffer end_render...

		// Clear framebuffers contents
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// The rest of the render systems will now run (see game manager
		// for system order)
				
	}
	
}

void OpenGL::OpenGLFrameBufferRenderer::end_render(entt::registry& registry) const{

	// After the other render systems have run:
	auto view = registry.view<FrameBufferComponent, ShaderComponent>();

	for (auto entity : view) {
		auto& framebuffer_component = view.get<FrameBufferComponent>(entity);
		auto& shader_component = view.get<ShaderComponent>(entity);

		// Bind back to default framebuffer
		framebuffer_component.m_frame_buffer->unbind();

		// Disable depth test so screen-space quad is not discarded (due to
		// depth test)
		glDisable(GL_DEPTH_TEST);

		// Clear all buffers
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
		glClear(GL_COLOR_BUFFER_BIT); //TODO depth buffer bit needed here?

		// Activate our framebuffer shader
		shader_component.m_shader_program->bind();

		// Bind the framebuffer quad vao and color texture:
		// TODO add check if texture attachment or render attachment is not initialized?
		// TODO 2 make these into bind functions instead?
		glBindVertexArray(framebuffer_component.m_frame_buffer->get_framebuffer_quad_vao());

		glActiveTexture(GL_TEXTURE0); //TODO I should make the framebuffer handle this
		glBindTexture(GL_TEXTURE_2D, framebuffer_component.m_frame_buffer->get_framebuffer_texture_handle());


		
		glDrawArrays(GL_TRIANGLES, 0, 6);		
		// glBindTexture(GL_TEXTURE_2D, 0);
		// glBindVertexArray(0);

		shader_component.m_shader_program->unbind();

	}
	
}
