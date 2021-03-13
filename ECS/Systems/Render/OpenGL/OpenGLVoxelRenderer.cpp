#include "OpenGLVoxelRenderer.h"
#include "../../Matrix/MatrixFunctions.h"
#include "../../../Components/Shader/VoxelShader.h"
#include "../../../Components/Voxel/ChunkComponent.h"
#include "../../../Components/Transform/TransformComponent.h"
#include <glad/glad.h>

//TODO This is no longer an open gl render.  its just a renderer

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

			glBindVertexArray(chunk.m_chunk->get_vao());
			glDrawArrays(GL_TRIANGLES, 0, vertex_qty);
			glBindVertexArray(0);

			shader.m_shader_program->unbind();
		}
				
	}
	
}
