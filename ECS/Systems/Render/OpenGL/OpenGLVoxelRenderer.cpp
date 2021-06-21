#include "OpenGLVoxelRenderer.h"
#include "../../Matrix/MatrixFunctions.h"
#include "../../ResourceManagement/ShaderResource.h"
#include "../../../Components/Voxel/ChunkComponent.h"
#include "../../../Components/Shader/VoxelShaderComponent.h"
#include "../../../Components/Transform/TransformComponent.h"
#include <glad/glad.h>

void OpenGL::OpenGLVoxelRenderer::render(entt::registry& registry, Camera& camera) const{

	const std::shared_ptr<IShaderProgram> voxel_shader = ShaderResource::get("voxel_shader");
	voxel_shader->bind();
	
	registry.view<ChunkComponent, TransformComponent, VoxelShaderComponent>().each([](auto& chunk, auto& transform, auto& shader) {

		if (chunk.m_chunk->get_in_camera_range()) {
			const int vertex_qty = chunk.m_chunk->get_vertex_qty();
			if (vertex_qty != 0) {				
				shader.m_shader_program->set_uniform("model_matrix", transform.m_model_matrix, false);
				shader.m_shader_program->set_uniform("normal_matrix", MatrixFunctions::get_normal_matrix(transform.m_model_matrix), false);
				
				glBindVertexArray(chunk.m_chunk->get_vao());
				glDrawArrays(GL_TRIANGLES, 0, vertex_qty);
				glBindVertexArray(0);
			}			
		}

	});
	voxel_shader->unbind();		
}
