#pragma once
#include "../Voxel/Chunk/Chunk.h"
#include "../Voxel/Neutral/AdjacentChunkPosition.h"
#include "../../World/WorldPosition.h"
#include "IVboVaoPool.h"
#include <unordered_map>

//TODO make pool raw pointer (and unique where its actually held).

class VoxelResource{

public:
	VoxelResource();
	~VoxelResource();

	[[nodiscard]] Chunk* get_chunk(const WorldPosition& world_position) const;
	[[nodiscard]] std::unordered_map<WorldPosition, std::unique_ptr<Chunk>, WorldPositionHash>& get_chunkmap();
	
	void set_all_chunk_neighbors() const;
	void set_specific_chunk_neighbors(const std::vector<WorldPosition>& chunk_positions) const;
	void set_vao_vbo_pool(const std::shared_ptr<IVboVaoPool>& pool);

	void load_xyz_chunk_range(const int x_chunk_qty, const int y_chunk_qty, const int z_chunk_qty);
	void load_multiple_chunks(const std::vector<WorldPosition>& world_positions);
	void load_individual_chunk(const WorldPosition& world_position);

	void load_vbo_vao_into_chunk(const WorldPosition& world_position) const;
	void unload_vbo_vao_into_pool(const WorldPosition& world_position) const;

	void destroy_all();		
			
private:			
	[[nodiscard]] Chunk* get_adjacent_chunk(const WorldPosition& world_position, const AdjacentChunkPosition adjacent_chunk) const;
	void set_individual_chunk_neighbors(Chunk* chunk) const;

	[[nodiscard]] bool adjacent_chunk_exists(const WorldPosition& world_position, const AdjacentChunkPosition adjacent_chunk) const;
	[[nodiscard]] bool chunk_exists(const WorldPosition& world_position) const;			
	void unload_vbo_vao_into_pool(Chunk* chunk) const;
	
	std::unordered_map<WorldPosition, std::unique_ptr<Chunk>, WorldPositionHash> m_chunkmap;
	std::shared_ptr<IVboVaoPool> m_vao_vbo_pool;
};