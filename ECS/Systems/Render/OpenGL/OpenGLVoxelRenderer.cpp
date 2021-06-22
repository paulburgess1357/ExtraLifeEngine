#include "OpenGLVoxelRenderer.h"
#include "../../ResourceManagement/ShaderResource.h"
#include "../../ResourceManagement/VoxelResource.h"
#include "../../ECS/Systems/Voxel/VoxelInRangeUpdater.h"
#include <glad/glad.h>


void OpenGL::OpenGLVoxelRenderer::render() const{

	const std::shared_ptr<IShaderProgram> voxel_shader = ShaderResource::get("voxel_shader");
	voxel_shader->bind();

	std::vector<WorldPosition> chunks_in_range = VoxelInRangeUpdater::get_chunks_in_range();
	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& chunkmap = VoxelResource::get_chunkmap();
	
	for(const auto& world_position : chunks_in_range){
		const std::shared_ptr<Chunk> current_chunk = chunkmap[world_position];
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