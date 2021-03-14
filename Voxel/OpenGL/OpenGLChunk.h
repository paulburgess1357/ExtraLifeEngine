#pragma once
#include "../Chunk/Chunk.h"
#include "../Neutral/WorldPosition.h"

namespace OpenGL{
	
	class OpenGLChunk : public Chunk {

	public:
		OpenGLChunk(const WorldPosition& starting_world_position);
		~OpenGLChunk();
		
		[[nodiscard]] unsigned int get_vao() const override;
		[[nodiscard]] unsigned int get_vbo() const override;
		
	private:		
		void initialize_vbo_vao();
			
		unsigned int m_vbo;
		unsigned int m_vao;
	};
	
} // namespace OpenGL