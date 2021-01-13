#include "ChunkManager.h"
#include "../OpenGL/OpenGLChunk.h"
#include "../../Utility/FatalError.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"

void ChunkManager::load(const WorldPosition& m_world_position, const std::shared_ptr<IShaderProgram>& shader_program) {

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		m_chunkmap[m_world_position] = std::make_shared<OpenGL::OpenGLChunk>(m_world_position, shader_program);
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
