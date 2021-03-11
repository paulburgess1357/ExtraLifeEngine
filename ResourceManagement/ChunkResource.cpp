#include "ChunkResource.h"
#include "../Voxel/OpenGL/OpenGLChunk.h"
#include "../../Utility/FatalError.h"
#include "../../Environment/Neutral/API/GraphicsAPI.h"

std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash> ChunkResource::m_chunkmap;

void ChunkResource::load(const int x_chunk_qty, const int y_chunk_qty, const int z_chunk_qty) {

	// As chunks are loaded they check chunks next to them and draw vertices
	// based on the adjacent chunk values.  This means that the chunk variable
	// 'm_block_types' must be loaded prior to the graphics data being loaded
	// in the update function.

	for (int x = 0; x < x_chunk_qty; x++) {
		for (int y = 0; y < y_chunk_qty; y++) {
			for (int z = 0; z < z_chunk_qty; z++) {
				load_individual_chunk(WorldPosition{ x * x_block_qty, y * y_block_qty, z * z_block_qty });
			}
		}
	}

	set_all_chunk_neighbors();
}

void ChunkResource::load_individual_chunk(const WorldPosition& world_position) {

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		m_chunkmap[world_position] = std::make_shared<OpenGL::OpenGLChunk>(world_position);
		return;
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan chunk type does not exist!.");
		return;
	}

	FatalError::fatal_error("Unknown graphics API type.  Cannot create chunk for chunk manager.");
}

void ChunkResource::set_all_chunk_neighbors() {

	// Each individual chunk is surrounded by neighbors.  This sets
	// pointers inside each chunk towards its neighbors

	for (auto& chunk : m_chunkmap) {
		set_individual_chunk_neighbors(chunk.first, chunk.second);
	}
}

void ChunkResource::set_individual_chunk_neighbors(const WorldPosition& world_position, std::shared_ptr<Chunk>& chunk) {

	if (adjacent_chunk_exists(world_position, AdjacentChunkPosition::LEFT)) {
		const std::shared_ptr<Chunk> adjacent_chunk = get_adjacent_chunk(world_position, AdjacentChunkPosition::LEFT);
		chunk->set_left_adjacent_chunk(adjacent_chunk);
	}

	if (adjacent_chunk_exists(world_position, AdjacentChunkPosition::RIGHT)) {
		const std::shared_ptr<Chunk> adjacent_chunk = get_adjacent_chunk(world_position, AdjacentChunkPosition::RIGHT);
		chunk->set_right_adjacent_chunk(adjacent_chunk);
	}

	if (adjacent_chunk_exists(world_position, AdjacentChunkPosition::TOP)) {
		const std::shared_ptr<Chunk> adjacent_chunk = get_adjacent_chunk(world_position, AdjacentChunkPosition::TOP);
		chunk->set_top_adjacent_chunk(adjacent_chunk);
	}

	if (adjacent_chunk_exists(world_position, AdjacentChunkPosition::BOTTOM)) {
		const std::shared_ptr<Chunk> adjacent_chunk = get_adjacent_chunk(world_position, AdjacentChunkPosition::BOTTOM);
		chunk->set_bottom_adjacent_chunk(adjacent_chunk);
	}

	if (adjacent_chunk_exists(world_position, AdjacentChunkPosition::FRONT)) {
		const std::shared_ptr<Chunk> adjacent_chunk = get_adjacent_chunk(world_position, AdjacentChunkPosition::FRONT);
		chunk->set_front_adjacent_chunk(adjacent_chunk);
	}

	if (adjacent_chunk_exists(world_position, AdjacentChunkPosition::BACK)) {
		const std::shared_ptr<Chunk> adjacent_chunk = get_adjacent_chunk(world_position, AdjacentChunkPosition::BACK);
		chunk->set_back_adjacent_chunk(adjacent_chunk);
	}

}

bool ChunkResource::adjacent_chunk_exists(const WorldPosition& world_position, AdjacentChunkPosition adjacent_chunk) {

	bool chunk_exists_result = false;

	switch (adjacent_chunk) {

	case AdjacentChunkPosition::LEFT:
		chunk_exists_result = chunk_exists(WorldPosition(world_position.x - x_block_qty, world_position.y, world_position.z));
		break;

	case AdjacentChunkPosition::RIGHT:
		chunk_exists_result = chunk_exists(WorldPosition(world_position.x + x_block_qty, world_position.y, world_position.z));
		break;

	case AdjacentChunkPosition::TOP:
		chunk_exists_result = chunk_exists(WorldPosition(world_position.x, world_position.y + y_block_qty, world_position.z));
		break;

	case AdjacentChunkPosition::BOTTOM:
		chunk_exists_result = chunk_exists(WorldPosition(world_position.x, world_position.y - y_block_qty, world_position.z));
		break;

	case AdjacentChunkPosition::FRONT:
		chunk_exists_result = chunk_exists(WorldPosition(world_position.x, world_position.y, world_position.z + z_block_qty));
		break;

	case AdjacentChunkPosition::BACK:
		chunk_exists_result = chunk_exists(WorldPosition(world_position.x, world_position.y, world_position.z - z_block_qty));
		break;

	default:
		FatalError::fatal_error("Unknown adjacent chunk position");
	}

	return chunk_exists_result;

}

std::shared_ptr<Chunk> ChunkResource::get_adjacent_chunk(const WorldPosition& world_position, const AdjacentChunkPosition adjacent_chunk) {

	WorldPosition adjacent_world_position;

	switch (adjacent_chunk) {

	case AdjacentChunkPosition::LEFT:
		adjacent_world_position = WorldPosition(world_position.x - x_block_qty, world_position.y, world_position.z);
		break;

	case AdjacentChunkPosition::RIGHT:
		adjacent_world_position = WorldPosition(world_position.x + x_block_qty, world_position.y, world_position.z);
		break;

	case AdjacentChunkPosition::TOP:
		adjacent_world_position = WorldPosition(world_position.x, world_position.y + y_block_qty, world_position.z);
		break;

	case AdjacentChunkPosition::BOTTOM:
		adjacent_world_position = WorldPosition(world_position.x, world_position.y - y_block_qty, world_position.z);
		break;

	case AdjacentChunkPosition::FRONT:
		adjacent_world_position = WorldPosition(world_position.x, world_position.y, world_position.z + z_block_qty);
		break;

	case AdjacentChunkPosition::BACK:
		adjacent_world_position = WorldPosition(world_position.x, world_position.y, world_position.z - z_block_qty);
		break;

	default:
		FatalError::fatal_error("Unknown adjacent chunk position");
	}

	return get_chunk(adjacent_world_position);
}

bool ChunkResource::chunk_exists(const WorldPosition& world_position) {
	return m_chunkmap.count(world_position);
}

std::shared_ptr<Chunk> ChunkResource::get_chunk(const WorldPosition& world_position) {
	return m_chunkmap.at(world_position);
}

void ChunkResource::destroy_all(){
	// Chunk destructor(s) are called (i.e. based on Graphics API)
	m_chunkmap.clear();
}
