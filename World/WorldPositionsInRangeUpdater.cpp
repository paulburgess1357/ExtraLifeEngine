#include "WorldPositionsInRangeUpdater.h"
#include "../Voxel/Chunk/Chunk.h"

WorldPositionsInRangeUpdater::WorldPositionsInRangeUpdater(const int x_range, const int y_range, const int z_range, const Camera& camera)
	:m_camera_old_world_position{ -99, -99, -99 },
	 m_camera_new_world_position{ -99, -99, -99 },
	 m_x_range{ x_range },
	 m_y_range{ y_range },
	 m_z_range{ z_range },
	 m_camera_chunk_changed{ true }{

	 // Special use case (i.e. we don't want any voxels to be loaded/displayed)
	 if(!(m_x_range == 0 && m_y_range == 0 && m_z_range == 0)){
		 initialize_world_positions_in_camera_range(camera);
	 }
	 
}

WorldPositionsInRangeUpdater::WorldPositionsInRangeUpdater(const VoxelMetaData& voxel_range_data, const Camera& camera)
	:WorldPositionsInRangeUpdater{ voxel_range_data.m_voxel_x_range, voxel_range_data.m_voxel_y_range, voxel_range_data.m_voxel_z_range, camera } {
}


void WorldPositionsInRangeUpdater::initialize_world_positions_in_camera_range(const Camera& camera) {
	
	m_camera_old_world_position = get_nearest_world_position_to_camera(camera);
	m_camera_new_world_position = m_camera_old_world_position;
	
	const int x_range_qty_start = m_x_range * -1;
	const int x_range_qty_end = m_x_range + 1;

	const int y_range_qty_start = m_y_range * -1;
	const int y_range_qty_end = m_y_range + 1;

	const int z_range_qty_start = m_z_range * -1;
	const int z_range_qty_end = m_z_range + 1;

	for (int x = x_range_qty_start; x < x_range_qty_end; x++) {
		for (int y = y_range_qty_start; y < y_range_qty_end; y++) {
			for (int z = z_range_qty_start; z < z_range_qty_end; z++) {
				m_all_world_positions_in_range.emplace_back(m_camera_new_world_position.x + (x_block_qty * x), m_camera_new_world_position.y + (y_block_qty * y), m_camera_new_world_position.z + (z_block_qty * z));
			}
		}
	}

}

void WorldPositionsInRangeUpdater::update_world_position_vectors(const Camera& camera) {

	m_camera_chunk_changed = false;
	const WorldPosition nearest_chunk_to_camera = get_nearest_world_position_to_camera(camera);

	// Only update 'world position vectors' if the camera position has changed
	if (m_camera_new_world_position != nearest_chunk_to_camera) {
		m_camera_old_world_position = m_camera_new_world_position;
		m_camera_new_world_position = nearest_chunk_to_camera;
		m_camera_chunk_changed = true;
		calculate_all_world_positions_in_camera_range();
	}

}

const std::vector<WorldPosition>& WorldPositionsInRangeUpdater::get_all_world_positions_in_camera_range() const{
	return m_all_world_positions_in_range;
}

const std::vector<WorldPosition>& WorldPositionsInRangeUpdater::get_new_world_positions_in_camera_range() const{
	return m_new_world_positions_in_range;
}

const std::vector<WorldPosition>& WorldPositionsInRangeUpdater::get_old_world_positions_not_in_camera_range() const{
	return m_old_world_positions_not_in_range;
}

bool WorldPositionsInRangeUpdater::has_camera_chunk_changed() const{
	return m_camera_chunk_changed;
}

void WorldPositionsInRangeUpdater::calculate_all_world_positions_in_camera_range() {
	
	const WorldPosition world_position_difference = m_camera_new_world_position - m_camera_old_world_position;

	m_old_world_positions_not_in_range.clear();
	m_new_world_positions_in_range.clear();
	
	std::vector<WorldPosition> updated_world_positions_in_range;
	updated_world_positions_in_range.reserve(m_all_world_positions_in_range.size());
	
	for(const auto& old_world_position : m_all_world_positions_in_range){

		// Check if the old world position is in range of the new camera position.
		// If its not, place it in the m_old_world_positions_not_in_range vector
		if(!is_position_in_range(m_camera_new_world_position, old_world_position)){
			m_old_world_positions_not_in_range.emplace_back(old_world_position);
		}

		// Check if new position is in range of the old camera.  If it is not,
		// place it in the 'm_new_world_positions_in_range' vector
		const WorldPosition updated_world_position = old_world_position + world_position_difference;
		if(!is_position_in_range(m_camera_old_world_position, updated_world_position)){
			m_new_world_positions_in_range.emplace_back(updated_world_position);
		}
		
		updated_world_positions_in_range.emplace_back(updated_world_position);
	}

	m_all_world_positions_in_range = updated_world_positions_in_range;
	
}

WorldPosition WorldPositionsInRangeUpdater::get_nearest_world_position_to_camera(const Camera& camera) {
	const glm::vec3 camera_position = camera.get_camera_position();

	const int nearest_x_chunk = static_cast<int>(camera_position.x) / x_block_qty * x_block_qty;
	const int nearest_y_chunk = static_cast<int>(camera_position.y) / y_block_qty * y_block_qty;
	const int nearest_z_chunk = static_cast<int>(camera_position.z) / z_block_qty * z_block_qty;

	const WorldPosition new_camera_position = WorldPosition{ nearest_x_chunk, nearest_y_chunk, nearest_z_chunk };
	return new_camera_position;
}

bool WorldPositionsInRangeUpdater::is_position_in_range(const WorldPosition& base_world_position, const WorldPosition& evaluated_world_position) const{
	const bool x_in_range = is_position_in_range(base_world_position.x, evaluated_world_position.x, m_x_range, x_block_qty);
	const bool y_in_range = is_position_in_range(base_world_position.y, evaluated_world_position.y, m_y_range, y_block_qty);
	const bool z_in_range = is_position_in_range(base_world_position.z, evaluated_world_position.z, m_z_range, z_block_qty);
	return x_in_range && y_in_range && z_in_range;
}

bool WorldPositionsInRangeUpdater::is_position_in_range(const int base_axis_value, const int evaluated_axis_value, const int axis_range, const int axis_block_qty) {
	const int min_axis_value = base_axis_value - (axis_range * axis_block_qty);
	const int max_axis_value = base_axis_value + (axis_range * axis_block_qty);
	return evaluated_axis_value >= min_axis_value && evaluated_axis_value <= max_axis_value;	
}
