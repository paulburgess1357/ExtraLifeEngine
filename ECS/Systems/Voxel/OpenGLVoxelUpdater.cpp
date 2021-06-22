#include "OpenGLVoxelUpdater.h"
#include "VoxelInRangeUpdater.h"
#include "../../ECS/Components/Voxel/ChunkComponent.h"
#include "../../ResourceManagement/VoxelResource.h"
#include <glad/glad.h>

void OpenGL::OpenGLVoxelUpdater::update() const{

	std::vector<WorldPosition> chunks_in_range = VoxelInRangeUpdater::get_chunks_in_range();
	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& chunkmap = VoxelResource::get_chunkmap();
	
	for(const auto& world_position : chunks_in_range){
		const std::shared_ptr<Chunk> current_chunk = chunkmap[world_position];
		if(current_chunk->update_required()){
			current_chunk->set_update_required(false);

			std::vector<VertexAndNormals> chunk_data = current_chunk->load_chunk_data();
			if (current_chunk->get_vertex_qty() != 0) {

				// Bind Buffers
				glBindVertexArray(current_chunk->get_vao());
				glBindBuffer(GL_ARRAY_BUFFER, current_chunk->get_vbo());

				// Store Data
				glBufferData(GL_ARRAY_BUFFER, chunk_data.size() * sizeof(VertexAndNormals), &chunk_data.front(), GL_STATIC_DRAW);

				// Vertex Data
				glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, 7 * sizeof(unsigned char), (void*)0);
				glEnableVertexAttribArray(0);

				// Normals
				glVertexAttribPointer(1, 3, GL_BYTE, GL_FALSE, 7 * sizeof(unsigned char), (void*)(4 * sizeof(unsigned char)));
				glEnableVertexAttribArray(1);

				// Unbind
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
			}						
		}		
	}
	
}
