#pragma once
#include "../../Camera/Camera.h"
#include "../../World/WorldPosition.h"

class WorldPositionsInRangeUpdater{
	
public:
	static void initialize_world_positions_in_camera_range(const Camera& camera);
	static void update_world_position_vectors(const Camera& camera);
	static std::vector<WorldPosition> get_all_world_positions_in_camera_range();
	static std::vector<WorldPosition> get_new_world_positions_in_camera_range();
	static std::vector<WorldPosition> get_old_world_positions_not_in_camera_range();

	static bool has_camera_chunk_changed();
		
private:
	WorldPositionsInRangeUpdater() = default;
	
	static void calculate_all_world_positions_in_camera_range();
	static WorldPosition get_nearest_world_position_to_camera(const Camera& camera);
	
	static bool is_position_in_range(const WorldPosition& base_world_position, const WorldPosition& evaluated_world_position);
	static bool is_position_in_range(const int base_axis_value, const int evaluated_axis_value, const int axis_range, const int axis_block_qty);
	
	static WorldPosition m_camera_old_world_position;
	static WorldPosition m_camera_new_world_position;
	
	static std::vector<WorldPosition> m_all_world_positions_in_range;
	static std::vector<WorldPosition> m_new_world_positions_in_range;
	static std::vector<WorldPosition> m_old_world_positions_not_in_range;

	static int m_x_range;
	static int m_y_range;
	static int m_z_range;

	static bool m_camera_chunk_changed;
	
};