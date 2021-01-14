#include "ChunkManager.h"
#include "../OpenGL/OpenGLChunk.h"
#include "../../Utility/FatalError.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"

// I need to initalize all chunk types before I build out the actual graphics data...
// Otherwise when I get a pointer to the neighboring chunk, those types may not be set yet.
// Currently this happens

void ChunkManager::load(const WorldPosition& m_world_position, const std::shared_ptr<IShaderProgram>& shader_program) {

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		m_chunkmap[m_world_position] = std::make_shared<OpenGL::OpenGLChunk>(m_world_position, shader_program, shared_from_this());
		return;
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan chunk type does not exist!.");
		return;
	}

	FatalError::fatal_error("Unknown graphics API type.  Cannot create chunk for chunk manager.");		
}

void ChunkManager::update() const{
	for (const auto& chunk : m_chunkmap) {
		chunk.second->update();
	}
}

void ChunkManager::render() const {
	for (const auto& chunk : m_chunkmap) {
		chunk.second->render();
	}
}

std::shared_ptr<IChunk> ChunkManager::get(const WorldPosition& m_world_position){
	return m_chunkmap.at(m_world_position);
}


