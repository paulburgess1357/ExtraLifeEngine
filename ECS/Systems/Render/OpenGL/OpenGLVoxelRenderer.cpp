#include "OpenGLVoxelRenderer.h"
#include "../../ResourceManagement/ChunkResource.h"
#include <glad/glad.h>

void OpenGL::OpenGLVoxelRenderer::render(entt::registry& registry, Camera& camera) const{

	for(const auto& chunk : ChunkResource::m_chunkmap){

		// Render chunk if it isn't empty
		if(!chunk.second->is_empty()){

			std::shared_ptr<IShaderProgram> shader_program = chunk.second->get_shader_program();
			
			shader_program->set_uniform("model_matrix", chunk.second->get_model_matrix());
			shader_program->set_uniform("normal_matrix", chunk.second->get_normal_matrix());
			shader_program->bind();

			// NOTE: each shader program is initialized with its own handle.  This means that I need to create the same number of shader programs as the number of chunks.  Each shader program would have its own handle.
			// Alternatively, I can test setting the shader program handle from the Chunk, but that sounds messier.  Right now each chunk has its own vao/vbo.  I need to move this out of the chunk and into the shader program
			glBindVertexArray(m_vao);
			glDrawArrays(GL_TRIANGLES, 0, chunk.second->get_vertex_qty());
			glBindVertexArray(0);

			shader_program->unbind();
		}

		
	}
	
}
