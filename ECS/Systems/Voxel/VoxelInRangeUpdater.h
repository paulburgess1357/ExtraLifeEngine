#pragma once
#include "../../Camera/Camera.h"
#include "../../Voxel/Neutral/WorldPosition.h"
#include "../../Voxel/Chunk/ChunkInRange.h"
#include <entt/entity/registry.hpp>

class VoxelInRangeUpdater{
	
public:
	static std::vector<WorldPosition> get_chunks_in_range();
	static void load_in_range_chunks(const Camera& camera, entt::registry& registry, const int x_range, const int y_range, const int z_range);
	
private:
	static WorldPosition get_nearest_chunk_coords_to_camera(const Camera& camera);
	static std::vector<WorldPosition> filter_to_new_world_positions(std::vector<WorldPosition>& chunks_in_range);
	static void load_new_chunks_in_range(std::vector<WorldPosition>& chunks_in_range);
	
	static WorldPosition m_camera_chunk_coords;
	static std::vector<WorldPosition> m_chunks_in_range;
};

