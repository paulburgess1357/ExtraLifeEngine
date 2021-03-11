#pragma once
#include "../Voxel/Chunk/Chunk.h"
#include "../Voxel/Neutral/WorldPosition.h"
#include "../Voxel/Neutral/AdjacentChunkPosition.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <unordered_map>


class ChunkResource{

public:	
	static void load(const int x_chunk_qty, const int y_chunk_qty, const int z_chunk_qty);
	static void destroy_all();

	static std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash> m_chunkmap;
	
private:	
	[[nodiscard]] static std::shared_ptr<Chunk> get_chunk(const WorldPosition& world_position);
	
	static void load_individual_chunk(const WorldPosition& world_position);
	static void set_all_chunk_neighbors();
	static void set_individual_chunk_neighbors(const WorldPosition& world_position, std::shared_ptr<Chunk>& chunk);
	
	[[nodiscard]] static std::shared_ptr<Chunk> get_adjacent_chunk(const WorldPosition& world_position, const AdjacentChunkPosition adjacent_chunk);
	[[nodiscard]] static bool adjacent_chunk_exists(const WorldPosition& world_position, AdjacentChunkPosition adjacent_chunk);
	[[nodiscard]] static bool chunk_exists(const WorldPosition& world_position);
	
	ChunkResource() = default;
	
};

