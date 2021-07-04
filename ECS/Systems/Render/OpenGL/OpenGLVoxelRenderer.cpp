#include "OpenGLVoxelRenderer.h"
#include "../../ResourceManagement/ShaderResource.h"
#include "../../ResourceManagement/VoxelResource.h"
#include "../../World/WorldPositionsInRangeUpdater.h"
#include <glad/glad.h>

OpenGL::OpenGLVoxelRenderer::OpenGLVoxelRenderer(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range, IShaderProgram& shader_program)
	:IVoxelRenderer{ voxel_resource, world_positions_in_range, shader_program} {
}

void OpenGL::OpenGLVoxelRenderer::render() const{

	m_voxel_shader_program.bind();

	const std::vector<WorldPosition>& chunks_in_range = m_world_positions_in_range_updater.get_all_world_positions_in_camera_range();
	
	for(const auto& world_position : chunks_in_range){
		const Chunk* current_chunk = m_voxel_resource.get_chunk(world_position);
		const int vertex_qty = current_chunk->get_vertex_qty();

		if(vertex_qty != 0){
			m_voxel_shader_program.set_uniform("model_matrix", current_chunk->get_model_matrx(), false);
			m_voxel_shader_program.set_uniform("normal_matrix", current_chunk->get_normal_matrx(), false);

			glBindVertexArray(current_chunk->get_vao());
			glDrawArrays(GL_TRIANGLES, 0, vertex_qty);
			glBindVertexArray(0);			
		}		
	}		

	m_voxel_shader_program.unbind();
}