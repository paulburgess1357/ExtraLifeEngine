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

// **************************** Warning ********************************
// Note if i had multiple framebuffers, issues would occur as they would start
// trying to bind over each other.  I need to work in multiple framebuffers into
// this system properly.

void OpenGL::OpenGLFrameBufferRenderer::start_render(entt::registry& registry) const{

	// Before all render systems have run:
	registry.view<FrameBufferComponent, ShaderComponent>().each([](auto& framebuffer_component, auto& shader_component) {

		// Handle window resizes
		framebuffer_component.m_frame_buffer->update_scaling();

		// Set custom frame buffer as active
		framebuffer_component.m_frame_buffer->bind();

		// Clear custom framebuffers contents
		framebuffer_component.m_frame_buffer->clear_buffer();

		// Depth testing necessary (normally disabled for on-screen quad)
		// Only necessary to enable if you disable depth testing in the
		// 'end_render' function.  However, you can simply avoid that call
		// by rending the quad last over everything else. (See framebuffer
		// shader for additional info).
		// glEnable(GL_DEPTH_TEST);

		// The rest of the render systems will now run (see game manager
		// for system order).  The scene is rendered like normal except
		// now we have our framebuffer bound instead of the default framebuffer


		});
	
}

void OpenGL::OpenGLFrameBufferRenderer::end_render(entt::registry& registry) const{

	// After the other render systems have run:
	registry.view<FrameBufferComponent, ShaderComponent>().each([](auto& framebuffer_component, auto& shader_component) {

		// Bind back to default framebuffer
		framebuffer_component.m_frame_buffer->unbind();

		// Disable depth test (ensures quad is drawn in front of everything)
		// This is handled in both the shader and by drawing this last.
		// See the shader for more info.
		// glDisable(GL_DEPTH_TEST);

		// Bind the framebuffer shader, quad vao, and color texture:
		shader_component.m_shader_program->bind();
		framebuffer_component.m_frame_buffer->bind_framebuffer_quad();
		framebuffer_component.m_frame_buffer->bind_framebuffer_texture();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		framebuffer_component.m_frame_buffer->unbind_framebuffer_texture();
		framebuffer_component.m_frame_buffer->unbind_framebuffer_quad();
		shader_component.m_shader_program->unbind();

		});
	
}
