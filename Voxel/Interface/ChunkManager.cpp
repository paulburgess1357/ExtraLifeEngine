#include "ChunkManager.h"
#include "../OpenGL/OpenGLChunk.h"
#include "../../Utility/FatalError.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"

void ChunkManager::load(const int size_x, const int size_y, const int size_z, const std::shared_ptr<IShaderProgram>& shader_program){

	// As chunks are loaded they check chunks next to them and draw vertices
	// based on the adjacent chunk values.  This means that the chunk variable
	// 'm_block_types' must be loaded prior to the graphics data being loaded
	// in the update function.
	
	for(int x = 0; x < size_x; x++){
		for(int y = 0; y< size_y; y++){
			for(int z = 0; z < size_z; z++){
				load(WorldPosition{ x * CX, y * CY, z * CZ }, shader_program);
			}
		}
	}	
}

void ChunkManager::load(const WorldPosition& world_position, const std::shared_ptr<IShaderProgram>& shader_program) {

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		m_chunkmap[world_position] = std::make_shared<OpenGL::OpenGLChunk>(world_position, shader_program, shared_from_this());
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

std::shared_ptr<Chunk> ChunkManager::get(const WorldPosition& world_position) const{
	return m_chunkmap.at(world_position);
}

bool ChunkManager::adjacent_chunk_exists(const WorldPosition& world_position, AdjacentChunkPosition adjacent_chunk) const{

	bool chunk_exists_result = false;

	switch (adjacent_chunk) {

	case AdjacentChunkPosition::LEFT:
		chunk_exists_result = chunk_exists(WorldPosition(world_position.x - CX, world_position.y, world_position.z));
		break;

	case AdjacentChunkPosition::RIGHT:
		chunk_exists_result = chunk_exists(WorldPosition(world_position.x + CX, world_position.y, world_position.z));
		break;

	case AdjacentChunkPosition::TOP:
		chunk_exists_result = chunk_exists(WorldPosition(world_position.x, world_position.y + CY, world_position.z));
		break;

	case AdjacentChunkPosition::BOTTOM:
		chunk_exists_result = chunk_exists(WorldPosition(world_position.x, world_position.y - CY, world_position.z));
		break;

	case AdjacentChunkPosition::FRONT:
		chunk_exists_result = chunk_exists(WorldPosition(world_position.x, world_position.y, world_position.z + CZ));
		break;

	case AdjacentChunkPosition::BACK:
		chunk_exists_result = chunk_exists(WorldPosition(world_position.x, world_position.y, world_position.z - CZ));
		break;

	default:
		FatalError::fatal_error("Unknown adjacent chunk position");
	}

	return chunk_exists_result;
	
}


std::shared_ptr<Chunk> ChunkManager::get_adjacent_chunk(const WorldPosition& world_position, AdjacentChunkPosition adjacent_chunk) const{

	WorldPosition adjacent_world_position;
	
	switch (adjacent_chunk){

	case AdjacentChunkPosition::LEFT :
		adjacent_world_position = WorldPosition(world_position.x - CX, world_position.y, world_position.z);
		break;

	case AdjacentChunkPosition::RIGHT :
		adjacent_world_position = WorldPosition(world_position.x + CX, world_position.y, world_position.z);
		break;

	case AdjacentChunkPosition::TOP :
		adjacent_world_position = WorldPosition(world_position.x, world_position.y + CY, world_position.z);
		break;

	case AdjacentChunkPosition::BOTTOM:
		adjacent_world_position = WorldPosition(world_position.x, world_position.y - CY, world_position.z);
		break;

	case AdjacentChunkPosition::FRONT:
		adjacent_world_position = WorldPosition(world_position.x, world_position.y, world_position.z + CZ);
		break;

	case AdjacentChunkPosition::BACK:
		adjacent_world_position = WorldPosition(world_position.x, world_position.y, world_position.z - CZ);
		break;

	default:
		FatalError::fatal_error("Unknown adjacent chunk position");		
	}

	return get(adjacent_world_position);	
}




bool ChunkManager::chunk_exists(const WorldPosition& world_position) const{
	return m_chunkmap.count(world_position);
}

