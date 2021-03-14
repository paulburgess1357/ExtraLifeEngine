#include "OpenGLVoxelUpdater.h"
#include "../../ECS/Components/Voxel/ChunkComponent.h"
#include <glad/glad.h>

void OpenGL::OpenGLVoxelUpdater::update(entt::registry& registry) const{
	
	registry.view<ChunkComponent>().each([](auto& chunk) {

		if (chunk.m_chunk->update_required()) {
			chunk.m_chunk->set_update_required(false);
			
			std::vector<VertexAndNormals> chunk_data = chunk.m_chunk->load_chunk_data();

			if (chunk.m_chunk->get_vertex_qty() != 0) {
				// Bind Buffers
				glBindVertexArray(chunk.m_chunk->get_vao());
				glBindBuffer(GL_ARRAY_BUFFER, chunk.m_chunk->get_vbo());

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
		
	});
	
}