#pragma once

#include "OpenGLChunk.h"
#include "WorldPosition.h"
#include "../Environment/Interfaces/Shader/IShaderProgram.h"
#include <unordered_map>

namespace OpenGL{

	class OpenGLChunkManager {

	public:
		OpenGLChunkManager() = default;
		~OpenGLChunkManager() = default;

		//TODO make chunk resource that I can pre-load chunks...? That way I can just load the pointer and world position
		//TODO as the engine starts up, and just load from the resource when I need more?
		//
		
		void load(const WorldPosition& m_world_position, const std::shared_ptr<IShaderProgram>& shader_program);
		//void load(const std::shared_ptr<IShaderProgram>& shader_program);
		void update();
		void render();
						
	private:
		std::unordered_map<WorldPosition, std::shared_ptr<OpenGLChunk>, WorldPositionHash> m_chunkmap;
		//OpenGL::OpenGLChunk* m_chunkmap[SCX][SCY][SCZ];
		
	};
	
} // namespace OpenGL


