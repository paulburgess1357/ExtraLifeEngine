#pragma once
#include "../../Camera/Camera.h"
#include "../../Voxel/Neutral/WorldPosition.h"

class VoxelInRangeUpdater{
	
public:
	static std::vector<WorldPosition> get_world_positions_in_camera_range();
	static void load_in_camera_range_chunks(const Camera& camera, const int x_range, const int y_range, const int z_range);
	
private:
	static std::vector<WorldPosition> calculate_world_positions_in_camera_range(const int x_range, const int y_range, const int z_range);
	static WorldPosition get_nearest_world_position_to_camera(const Camera& camera);
	static std::vector<WorldPosition> filter_to_non_loaded_new_world_positions(const std::vector<WorldPosition>& world_positions_in_range);
	
	static WorldPosition m_camera_chunk_world_position;
	static std::vector<WorldPosition> m_world_positions_in_range;
};

