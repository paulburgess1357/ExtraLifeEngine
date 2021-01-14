#pragma once
#include "../Interface/IChunk.h"
#include "../Interface/ChunkManager.h"
#include "../Neutral/WorldPosition.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <memory>

namespace OpenGL{
	
	class OpenGLChunk : public IChunk {

	public:
		OpenGLChunk(const WorldPosition& starting_world_position, 
			const std::shared_ptr<IShaderProgram>& shader_program,
			const std::shared_ptr<ChunkManager>& chunk_manager);
		~OpenGLChunk();
		
		void update() override;
		void render() const override;
		
	private:		
		void initialize_vbo_vao();
			
		unsigned int m_vbo;
		unsigned int m_vao;
		std::shared_ptr<ChunkManager> m_chunkmanager;
	};
	
} // namespace OpenGL



