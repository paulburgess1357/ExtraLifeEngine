#include "OpenGLVoxelRenderer.h"
#include "../../Matrix/MatrixFunctions.h"
#include "../../../Components/Shader/VoxelShader.h"
#include "../../../Components/Voxel/ChunkComponent.h"
#include "../../../Components/Transform/TransformComponent.h"
#include <glad/glad.h>

void OpenGL::OpenGLVoxelRenderer::render(entt::registry& registry, Camera& camera) const{

	auto view = registry.view<ChunkComponent, TransformComponent, VoxelShaderComponent>();
	for(auto entity : view){

		auto& chunk = view.get<ChunkComponent>(entity);
		auto& transform = view.get<TransformComponent>(entity);
		auto& shader = view.get<VoxelShaderComponent>(entity);

		const int vertex_qty = chunk.m_chunk->get_vertex_qty();
		
		// Skip drawing empty chunks
		if (vertex_qty != 0) {

			shader.m_shader_program->set_uniform("model_matrix", transform.m_model_matrix);
			shader.m_shader_program->set_uniform("normal_matrix", MatrixFunctions::get_normal_matrix(transform.m_model_matrix));
			
			shader.m_shader_program->bind();

			// TODO how to get m_vao? Its in the open gl chunk, but the chunk component is based on the parent class..  Create OpenGLChunkComponent?
			glBindVertexArray(chunk.m_chunk->get);
			glDrawArrays(GL_TRIANGLES, 0, vertex_qty);
			glBindVertexArray(0);

			shader.m_shader_program->unbind();
		}
				
	}

	
	registry.view<ChunkComponent, TransformComponent, VoxelShaderComponent>().each([](auto& chunk, auto& transform, auto& shader) {



		shader.m_shader_program->bind();


		
		//		glBindVertexArray(m_vao);
//		glDrawArrays(GL_TRIANGLES, 0, chunk.second->get_vertex_qty());
//		glBindVertexArray(0);





		
		shader.m_shader_program->unbind();

	});








	
	//for(const auto& chunk : ChunkResource::m_chunkmap){

	//	// Render chunk if it isn't empty
	//	if(!chunk.second->is_empty()){

	//		std::shared_ptr<IShaderProgram> shader_program = chunk.second->get_shader_program();
	//		
	//		shader_program->set_uniform("model_matrix", chunk.second->get_model_matrix());
	//		shader_program->set_uniform("normal_matrix", chunk.second->get_normal_matrix());
	//		shader_program->bind();

	//		// NOTE: each shader program is initialized with its own handle.  This means that I need to create the same number of shader programs as the number of chunks.  Each shader program would have its own handle.
	//		// Alternatively, I can test setting the shader program handle from the Chunk, but that sounds messier.  Right now each chunk has its own vao/vbo.  I need to move this out of the chunk and into the shader program
	//		glBindVertexArray(m_vao);
	//		glDrawArrays(GL_TRIANGLES, 0, chunk.second->get_vertex_qty());
	//		glBindVertexArray(0);

	//		shader_program->unbind();
	//	}

	//	
	//}
	
}
