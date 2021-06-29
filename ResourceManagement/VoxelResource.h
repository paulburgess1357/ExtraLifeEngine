#pragma once
#include "../Voxel/Chunk/Chunk.h"
#include "../Voxel/Neutral/AdjacentChunkPosition.h"
#include "../../World/WorldPosition.h"
#include "IVboVaoPool.h"
#include <unordered_map>

class VoxelResource{

public:	
	static void load_xyz_chunk_range(const int x_chunk_qty, const int y_chunk_qty, const int z_chunk_qty);
	static void load_multiple_chunks(const std::vector<WorldPosition>& world_positions);
	static void load_individual_chunk(const WorldPosition& world_position);
	static void set_all_chunk_neighbors();
	static void set_specific_chunk_neighbors(const std::vector<WorldPosition>& chunk_positions);

	static void load_vbo_vao_into_chunk(const WorldPosition& world_position);
	static void unload_vbo_vao_into_pool(const WorldPosition& world_position);

	static void destroy_all();
	
	[[nodiscard]] static std::shared_ptr<Chunk> get_chunk(const WorldPosition& world_position);	
	[[nodiscard]] static std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& get_chunkmap();

	static void set_vao_vbo_pool(std::shared_ptr<IVboVaoPool> pool);
			
private:	
	VoxelResource() = default;
	
	[[nodiscard]] static std::shared_ptr<Chunk> get_adjacent_chunk(const WorldPosition& world_position, const AdjacentChunkPosition adjacent_chunk);
	[[nodiscard]] static bool adjacent_chunk_exists(const WorldPosition& world_position, const AdjacentChunkPosition adjacent_chunk);
	[[nodiscard]] static bool chunk_exists(const WorldPosition& world_position);
		
	static void set_individual_chunk_neighbors(std::shared_ptr<Chunk>& chunk);
	static void unload_vbo_vao_into_pool(std::shared_ptr<Chunk>& chunk);
	
	static std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash> m_chunkmap;
	static std::shared_ptr<IVboVaoPool> m_vao_vbo_pool;
};