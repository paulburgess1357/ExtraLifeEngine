#include "OpenGLFrameBufferRenderer.h"
#include <glad/glad.h>

// Multiple framebuffer renders look like this:
// 1) Bind first framebuffer (start_render function)
// 2) Draw scene with all other draw functions outside this class (model/voxel/cube/etc.)
// 3) Bind the 2nd framebuffer
//	  Bind the 1st framebuffer shader/quad/texture
//	  Draw the 1st framebuffer quad
// 4) Bind the 3rd framebuffer
//	  Bind the 2nd framebuffer shader/quad/texture
//	  Draw the 2nd framebuffer quad
// 5) Bind the default framebuffer
//    Bind the 3rd framebuffer shader/quad/texture
//    Draw the 3rd framebuffer shader/quad/texture


OpenGL::OpenGLFrameBufferRenderer::OpenGLFrameBufferRenderer(FrameBufferHandler& framebuffer_handler)
	:IFrameBufferRenderer{ framebuffer_handler }{
}

void OpenGL::OpenGLFrameBufferRenderer::start_render() {

	const std::map<int, IFrameBuffer*>& active_framebuffers = m_framebuffer_handler.get_active_framebuffer_map();

	// Clear all framebuffers
	for(const auto& framebuffer : active_framebuffers){
		framebuffer.second->bind();
		framebuffer.second->clear_buffer();
		framebuffer.second->unbind();
	}
	
	// Bind First framebuffer and draw scene:
	if(!active_framebuffers.empty()){
		IFrameBuffer* first_framebuffer = active_framebuffers.begin()->second;

		// Handle window resizes
		first_framebuffer->update_scaling();

		// Set first framebuffer as active
		first_framebuffer->bind();

		// Clear custom framebuffers contents
		// first_framebuffer->clear_buffer();

		// Depth testing necessary (normally disabled for on-screen quad)
		// Only necessary to enable if you disable depth testing in the
		// 'end_render' function.  However, you can simply avoid that call
		// by rending the quad last over everything else. (See framebuffer
		// vertex shader for additional info).
		// glEnable(GL_DEPTH_TEST);

		// The rest of the render systems will now run (see game manager
		// for system order).  The scene is rendered like normal except
		// now we have our framebuffer bound instead of the default framebuffer
		// This will be drawn to the current bound framebuffer (the 1st one)
		
	}

}

void OpenGL::OpenGLFrameBufferRenderer::end_render() {

	const std::map<int, IFrameBuffer*>& active_framebuffers = m_framebuffer_handler.get_active_framebuffer_map();

	auto current_element = active_framebuffers.begin();
	auto previous_element = current_element;
	
	while(current_element != active_framebuffers.end()){

		// Skip first framebuffer as its already been bound
		// Note that the 1st framebuffer will be drawn (on the 2nd loop)
		if(current_element != active_framebuffers.begin()){

			// Bind current framebuffer
			current_element->second->bind();

			// Draw contents of previous framebuffer to current framebuffer
			previous_element->second->bind_framebuffer_shader();
			previous_element->second->bind_framebuffer_quad();
			previous_element->second->bind_framebuffer_texture();

			glDrawArrays(GL_TRIANGLES, 0, 6);

			previous_element->second->unbind_framebuffer_texture();
			previous_element->second->unbind_framebuffer_quad();
			previous_element->second->unbind_framebuffer_shader();
			
		}

		previous_element = current_element;
		++current_element;
		
	}

	// Bind the default framebuffer and draw the last framebuffer element
	// The loop above ensures that 'previous_element' is the last element
	// as 'current_element' will now point to the end() iterator (which
	// we know is the past-the-end position)

	// Check to ensure we have at least one framebuffer in the active
	// framebuffers (the same check can be done with empty()).
	// If the active framebuffer map was empty, 'current_element' would point
	// to the end() when calling begin().  'previous_element' is initially set
	// to current_element.  The loop would not run.  Therefore previous_element
	// would point to the end as well.
	if(previous_element != active_framebuffers.end()){
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		previous_element->second->bind_framebuffer_shader();
		previous_element->second->bind_framebuffer_quad();
		previous_element->second->bind_framebuffer_texture();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		previous_element->second->unbind_framebuffer_texture();
		previous_element->second->unbind_framebuffer_quad();
		previous_element->second->unbind_framebuffer_shader();
	}			
}



//TODO the gamma framebuffer must be last if it exists.  To make things consistent,
// TODO it can also just be first if it exists.  NO ECS System.  Get framebuffer map and iterate
// TODO through it after the gamma as run (if it exists
//
// )

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

//void OpenGL::OpenGLFrameBufferRenderer::start_render() const{
//
//	// Before all render systems have run:
//	registry.view<FrameBufferComponent, ShaderComponent>().each([](auto& framebuffer_component, auto& shader_component) {
//
//		// Handle window resizes
//		framebuffer_component.m_frame_buffer->update_scaling();
//
//		// Set custom frame buffer as active
//		framebuffer_component.m_frame_buffer->bind();
//
//		// Clear custom framebuffers contents
//		framebuffer_component.m_frame_buffer->clear_buffer();
//
//		// Depth testing necessary (normally disabled for on-screen quad)
//		// Only necessary to enable if you disable depth testing in the
//		// 'end_render' function.  However, you can simply avoid that call
//		// by rending the quad last over everything else. (See framebuffer
//		// shader for additional info).
//		// glEnable(GL_DEPTH_TEST);
//
//		// The rest of the render systems will now run (see game manager
//		// for system order).  The scene is rendered like normal except
//		// now we have our framebuffer bound instead of the default framebuffer
//
//
//		});
//	
//}

//void OpenGL::OpenGLFrameBufferRenderer::end_render() const{
//
//	// After the other render systems have run:
//	registry.view<FrameBufferComponent, ShaderComponent>().each([](auto& framebuffer_component, auto& shader_component) {
//
//		// Bind back to default framebuffer
//		framebuffer_component.m_frame_buffer->unbind();
//
//		// Disable depth test (ensures quad is drawn in front of everything)
//		// This is handled in both the shader and by drawing this last.
//		// See the shader for more info.
//		// glDisable(GL_DEPTH_TEST);
//
//		// Bind the framebuffer shader, quad vao, and color texture:
//		shader_component.m_shader_program->bind();
//		framebuffer_component.m_frame_buffer->bind_framebuffer_quad();
//		framebuffer_component.m_frame_buffer->bind_framebuffer_texture();
//
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		framebuffer_component.m_frame_buffer->unbind_framebuffer_texture();
//		framebuffer_component.m_frame_buffer->unbind_framebuffer_quad();
//		shader_component.m_shader_program->unbind();
//
//		});
//	
//}
