#pragma once
#include "../../Camera/Camera.h"
#include "../../Voxel/Neutral/WorldPosition.h"

class VoxelInRangeUpdater{
	
public:
	static void initialize_world_positions_in_camera_range();
	static std::vector<WorldPosition> get_world_positions_in_camera_range();
	static void load_in_camera_range_chunks(const Camera& camera);
		
private:
	static void calculate_new_old_world_positions_in_camera_range(const WorldPosition& old_world_position, const WorldPosition& new_world_position);
	static WorldPosition get_nearest_world_position_to_camera(const Camera& camera);
	static std::vector<WorldPosition> filter_to_non_loaded_new_world_positions();
	
	static WorldPosition m_camera_chunk_world_position;
	static std::vector<WorldPosition> m_all_world_positions_in_range;
	static std::vector<WorldPosition> m_new_world_positions_in_range;
	static std::vector<WorldPosition> m_old_world_positions_in_range;

	static int m_x_range;
	static int m_y_range;
	static int m_z_range;
	
};

