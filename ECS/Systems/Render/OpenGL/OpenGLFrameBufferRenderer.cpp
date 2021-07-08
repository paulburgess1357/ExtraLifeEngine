#include "OpenGLFrameBufferRenderer.h"
#include "../../ECS/Components/FrameBuffer/FrameBufferComponent.h"
#include "../../ECS/Components/Shader/ShaderComponent.h"
#include <glad/glad.h>

// The framebuffer has two parts start_render and end_render
//        Framebuffer start_render()
//        Cubemap render
//        Other renderer render()
//        Other renderer render()
//        Framebuffer end_render()

void OpenGL::OpenGLFrameBufferRenderer::start_render(entt::registry& registry) const{

	auto view = registry.view<FrameBufferComponent, ShaderComponent>();

	for (auto entity : view) {
		auto& framebuffer_component = view.get<FrameBufferComponent>(entity);

		// Handle window resizes
		framebuffer_component.m_frame_buffer->update_scaling();

		// Set custom frame buffer as active
		framebuffer_component.m_frame_buffer->bind();

		// Depth testing necessary (normally disabled for on-screen quad)
		glEnable(GL_DEPTH_TEST);

		// Clear custom framebuffers contents
		framebuffer_component.m_frame_buffer->clear_buffer();

		// The rest of the render systems will now run (see game manager
		// for system order).  The scene is rendered like normal except
		// now we have our framebuffer bound instead of the default framebuffer
				
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

		// Disable depth test (ensures quad is drawn in front of everything)
		glDisable(GL_DEPTH_TEST);
		
		// Bind the framebuffer shader, quad vao, and color texture:
		// TODO store pointer to shader in framebuffer?
		shader_component.m_shader_program->bind();
		framebuffer_component.m_frame_buffer->bind_framebuffer_quad();
		framebuffer_component.m_frame_buffer->bind_framebuffer_texture();
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		framebuffer_component.m_frame_buffer->unbind_framebuffer_texture();
		framebuffer_component.m_frame_buffer->unbind_framebuffer_quad();
		shader_component.m_shader_program->unbind();

	}
	
}
