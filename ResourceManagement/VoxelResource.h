#pragma once
#include "../Voxel/Chunk/Chunk.h"
#include "../Voxel/Neutral/WorldPosition.h"
#include "../Voxel/Neutral/AdjacentChunkPosition.h"
#include <unordered_map>

class VoxelResource{

public:	
	static void load(const int x_chunk_qty, const int y_chunk_qty, const int z_chunk_qty);
	[[nodiscard]] static std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& get_chunkmap();
	static void destroy_all();
	
private:	
	VoxelResource() = default;
	
	[[nodiscard]] static std::shared_ptr<Chunk> get_chunk(const WorldPosition& world_position);
	[[nodiscard]] static std::shared_ptr<Chunk> get_adjacent_chunk(const WorldPosition& world_position, const AdjacentChunkPosition adjacent_chunk);
	[[nodiscard]] static bool adjacent_chunk_exists(const WorldPosition& world_position, AdjacentChunkPosition adjacent_chunk);
	[[nodiscard]] static bool chunk_exists(const WorldPosition& world_position);
	
	static void load_individual_chunk(const WorldPosition& world_position);
	static void set_all_chunk_neighbors();
	static void set_individual_chunk_neighbors(const WorldPosition& world_position, std::shared_ptr<Chunk>& chunk);		

	static std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash> m_chunkmap;
		
};