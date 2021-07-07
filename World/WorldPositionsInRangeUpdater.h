#pragma once
#include "../../Camera/Camera.h"
#include "../../World/WorldPosition.h"

class WorldPositionsInRangeUpdater{
	
public:
	WorldPositionsInRangeUpdater(const int x_range, const int y_range, const int z_range, const Camera& camera);
	
	void initialize_world_positions_in_camera_range(const Camera& camera);
	void update_world_position_vectors(const Camera& camera);
	
	[[nodiscard]] const std::vector<WorldPosition>& get_all_world_positions_in_camera_range() const;
	[[nodiscard]] const std::vector<WorldPosition>& get_new_world_positions_in_camera_range() const;
	[[nodiscard]] const std::vector<WorldPosition>& get_old_world_positions_not_in_camera_range() const;
	[[nodiscard]] bool has_camera_chunk_changed() const;
		
private:	
	void calculate_all_world_positions_in_camera_range();
	
	[[nodiscard]] static WorldPosition get_nearest_world_position_to_camera(const Camera& camera);	
	[[nodiscard]] bool is_position_in_range(const WorldPosition& base_world_position, const WorldPosition& evaluated_world_position) const;
	[[nodiscard]] static bool is_position_in_range(const int base_axis_value, const int evaluated_axis_value, const int axis_range, const int axis_block_qty);
	
	WorldPosition m_camera_old_world_position;
	WorldPosition m_camera_new_world_position;

	int m_x_range;
	int m_y_range;
	int m_z_range;

	bool m_camera_chunk_changed;

	std::vector<WorldPosition> m_all_world_positions_in_range;
	std::vector<WorldPosition> m_new_world_positions_in_range;
	std::vector<WorldPosition> m_old_world_positions_not_in_range;
	
};
