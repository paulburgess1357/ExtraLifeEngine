#include "OpenGLVoxelRenderer.h"
#include "../../ResourceManagement/VoxelResource.h"
#include "../../World/WorldPositionsInRangeUpdater.h"
#include <glad/glad.h>

OpenGL::OpenGLVoxelRenderer::OpenGLVoxelRenderer(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range, IShaderProgram* shader_program)
	:IVoxelRenderer{ voxel_resource, world_positions_in_range, shader_program} {
}

// ************************ EXTREMELY IMPORTANT ***************************
// All shaders are working in view space.  The voxel shader is working
// in world space.  The normal matrix supplied does not take into account
// the view matrix.  The normal matrix for a voxel is created when the 
// Chunk is initialized.  This needs to be updated to take into account
// the view matrix.  You need to update the voxel renderer as well.  Right
// now an identify matrix is being used to bypass this issue.
// *************************************************************************

void OpenGL::OpenGLVoxelRenderer::render() const{

	if(m_voxel_shader_program != nullptr){
		
		const std::vector<WorldPosition>& chunks_in_range = m_world_positions_in_range_updater.get_all_world_positions_in_camera_range();
		if (!chunks_in_range.empty()) {

			m_voxel_shader_program->bind();

			for (const auto& world_position : chunks_in_range) {
				const Chunk* current_chunk = m_voxel_resource.get_chunk(world_position);
				const int vertex_qty = current_chunk->get_vertex_qty();

				if (vertex_qty != 0) {
					m_voxel_shader_program->set_uniform("model_matrix", current_chunk->get_model_matrx(), false);
					m_voxel_shader_program->set_uniform("normal_matrix", current_chunk->get_normal_matrx(), false);

					glBindVertexArray(current_chunk->get_vao());
					glDrawArrays(GL_TRIANGLES, 0, vertex_qty);
					glBindVertexArray(0);
				}
			}

			m_voxel_shader_program->unbind();
		}
		
	}
		
}
