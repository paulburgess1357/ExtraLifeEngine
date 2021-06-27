#include "VoxelInRangeUpdater.h"
#include "../../ResourceManagement/VoxelResource.h"

// TODO
// 1) Get m_new_world_positions_in_range working
// 2) Separate in world positions in range class from loading voxel data
// 3) Unload opengl resource
// 4) Reuse resource
// 5) Hope it improves things

WorldPosition VoxelInRangeUpdater::m_camera_old_world_position{ -99, -99, -99 };
WorldPosition VoxelInRangeUpdater::m_camera_new_world_position{ -99, -99, -99 };

std::vector<WorldPosition> VoxelInRangeUpdater::m_all_world_positions_in_range;
std::vector<WorldPosition> VoxelInRangeUpdater::m_new_world_positions_in_range;
std::vector<WorldPosition> VoxelInRangeUpdater::m_old_world_positions_not_in_range;

int VoxelInRangeUpdater::m_x_range = 10;
int VoxelInRangeUpdater::m_y_range = 3;
int VoxelInRangeUpdater::m_z_range = 10;

void VoxelInRangeUpdater::initialize_world_positions_in_camera_range(const Camera& camera) {
	
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

	load_non_loaded_voxel_data();
}

std::vector<WorldPosition> VoxelInRangeUpdater::get_world_positions_in_camera_range(){
	return m_all_world_positions_in_range;
}

void VoxelInRangeUpdater::load_in_camera_range_chunks(const Camera& camera) {
	
	const WorldPosition new_camera_chunk_world_position = get_nearest_world_position_to_camera(camera);	

	// Only update 'chunks in range' if the camera position has changed
	if (m_camera_new_world_position != new_camera_chunk_world_position) {		

		m_camera_old_world_position = m_camera_new_world_position;
		m_camera_new_world_position = new_camera_chunk_world_position;

		calculate_all_world_positions_in_camera_range();		
		load_non_loaded_voxel_data();
	}	
}

void VoxelInRangeUpdater::load_non_loaded_voxel_data(){
		
	// Filter to only new world positions (no old chunks allowed!)
	const std::vector<WorldPosition> non_loaded_world_positions = get_non_loaded_world_positions();

	// Load new chunks into voxel resource
	VoxelResource::load_multiple_chunks(non_loaded_world_positions);

	// Update chunk neighbors for both brand new chunks and existing
	// old chunks that are adjacent to the new chunks
	VoxelResource::set_specific_chunk_neighbors(non_loaded_world_positions);
}


void VoxelInRangeUpdater::calculate_all_world_positions_in_camera_range() {
	
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
		
		const WorldPosition updated_world_position = old_world_position + world_position_difference;
		// Check if new position is in range of the old camera.  If it is not,
		// place it in the 'm_new_world_positions_in_range' vector
		if(!is_position_in_range(m_camera_old_world_position, updated_world_position)){
			m_new_world_positions_in_range.emplace_back(updated_world_position);
		}
		
		updated_world_positions_in_range.emplace_back(updated_world_position);
	}

	m_all_world_positions_in_range = updated_world_positions_in_range;
	
}

std::vector<WorldPosition> VoxelInRangeUpdater::get_non_loaded_world_positions() {

	std::vector<WorldPosition> newchunks_positions;
	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& chunkmap = VoxelResource::get_chunkmap();

	for (const auto& world_position : m_all_world_positions_in_range) {
		if (chunkmap.count(world_position) == 0) {
			newchunks_positions.emplace_back(world_position);
		}
	}

	return newchunks_positions;
}

WorldPosition VoxelInRangeUpdater::get_nearest_world_position_to_camera(const Camera& camera){	
	const glm::vec3 camera_position = camera.get_camera_position();

	const int nearest_x_chunk = static_cast<int>(camera_position.x) / x_block_qty * x_block_qty;
	const int nearest_y_chunk = static_cast<int>(camera_position.y) / y_block_qty * y_block_qty;
	const int nearest_z_chunk = static_cast<int>(camera_position.z) / z_block_qty * z_block_qty;

	const WorldPosition new_camera_position = WorldPosition{ nearest_x_chunk, nearest_y_chunk, nearest_z_chunk };
	return new_camera_position;
}

bool VoxelInRangeUpdater::is_position_in_range(const WorldPosition& base_world_position, const WorldPosition& evaluated_world_position){
	const bool x_in_range = is_position_in_range(base_world_position.x, evaluated_world_position.x, m_x_range, x_block_qty);
    const bool y_in_range = is_position_in_range(base_world_position.y, evaluated_world_position.y, m_y_range, y_block_qty);
	const bool z_in_range = is_position_in_range(base_world_position.z, evaluated_world_position.z, m_z_range, z_block_qty);	
	return x_in_range && y_in_range && z_in_range;	
}


bool VoxelInRangeUpdater::is_position_in_range(const int base_axis_value, const int evaluated_axis_value, const int axis_range, const int axis_block_qty){

	const int min_axis_value = base_axis_value - (axis_range * axis_block_qty);
	const int max_axis_value = base_axis_value + (axis_range * axis_block_qty);

	return evaluated_axis_value >= min_axis_value && evaluated_axis_value <= max_axis_value;
	
}
