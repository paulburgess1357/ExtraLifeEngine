#include "OpenGLVoxelRenderer.h"
#include "../../ResourceManagement/ShaderResource.h"
#include "../../ResourceManagement/VoxelResource.h"
#include "../../World/WorldPositionsInRangeUpdater.h"
#include <glad/glad.h>

OpenGL::OpenGLVoxelRenderer::OpenGLVoxelRenderer(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range)
	:IVoxelRenderer{ voxel_resource, world_positions_in_range} {
}

void OpenGL::OpenGLVoxelRenderer::render() const{

	const std::shared_ptr<IShaderProgram> voxel_shader = ShaderResource::get("voxel_shader");
	voxel_shader->bind();

	const std::vector<WorldPosition>& chunks_in_range = m_world_positions_in_range_updater.get_all_world_positions_in_camera_range();
	
	for(const auto& world_position : chunks_in_range){
		const Chunk* current_chunk = m_voxel_resource.get_chunk(world_position);
		const int vertex_qty = current_chunk->get_vertex_qty();

		if(vertex_qty != 0){
			voxel_shader->set_uniform("model_matrix", current_chunk->get_model_matrx(), false);
			voxel_shader->set_uniform("normal_matrix", current_chunk->get_normal_matrx(), false);

			glBindVertexArray(current_chunk->get_vao());
			glDrawArrays(GL_TRIANGLES, 0, vertex_qty);
			glBindVertexArray(0);			
		}		
	}		

	voxel_shader->unbind();		
}