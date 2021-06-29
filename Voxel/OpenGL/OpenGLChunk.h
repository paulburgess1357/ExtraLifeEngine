#pragma once
#include "../Chunk/Chunk.h"
#include "../../World/WorldPosition.h"

namespace OpenGL{
	
	class OpenGLChunk : public Chunk {

	public:
		OpenGLChunk(const WorldPosition& starting_world_position, const unsigned int vbo, const unsigned int vao);
		~OpenGLChunk();
		
		[[nodiscard]] unsigned int get_vao() const override;
		[[nodiscard]] unsigned int get_vbo() const override;

		void set_vbo(const unsigned int vbo) override;
		void set_vao(const unsigned int vao) override;

		bool vbo_vao_initialized() const override;

		void destroy() const override;
		
	private:					
		unsigned int m_vbo;
		unsigned int m_vao;
				
	};
	
} // namespace OpenGL