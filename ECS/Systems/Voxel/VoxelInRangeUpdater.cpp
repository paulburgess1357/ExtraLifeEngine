#include "VoxelInRangeUpdater.h"
#include "../../ResourceManagement/VoxelResource.h"

//TODO Instead of limiting to just voxels, use the inrange to limit any objects to be within camera range.
//TODO Likely split this class up to have one that loads voxels, and another that simply tracks the world positions in range.

WorldPosition VoxelInRangeUpdater::m_camera_old_world_position{ -99, -99, -99 };
WorldPosition VoxelInRangeUpdater::m_camera_new_world_position{ -99, -99, -99 };

std::vector<WorldPosition> VoxelInRangeUpdater::m_all_world_positions_in_range;
std::vector<WorldPosition> VoxelInRangeUpdater::m_new_world_positions_in_range;
std::vector<WorldPosition> VoxelInRangeUpdater::m_old_world_positions_in_range;

int VoxelInRangeUpdater::m_x_range = 10;
int VoxelInRangeUpdater::m_y_range = 3;
int VoxelInRangeUpdater::m_z_range = 10;

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
		// m_camera_new_world_position = new_camera_chunk_world_position;

		// Filter to only new world positions (no old chunks allowed!)
		const std::vector<WorldPosition> new_world_positions_in_range = filter_to_non_loaded_new_world_positions();

		// Load new chunks into ecs and voxel resource
		VoxelResource::load_multiple_chunks(new_world_positions_in_range);

		// Update chunk neighbors for both brand new chunks and existing
		// old chunks that are adjacent to the new chunks
		VoxelResource::set_specific_chunk_neighbors(new_world_positions_in_range);
	}	
}

void VoxelInRangeUpdater::initialize_world_positions_in_camera_range(const WorldPosition& starting_camera_position){

	m_camera_old_world_position = starting_camera_position;
	m_camera_new_world_position = starting_camera_position;
	
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


void VoxelInRangeUpdater::calculate_all_world_positions_in_camera_range() {
	const WorldPosition world_position_difference = m_camera_new_world_position - m_camera_old_world_position;
	
	std::vector<WorldPosition> new_world_positions_in_range;
	new_world_positions_in_range.reserve(m_all_world_positions_in_range.size());
	
	for(const auto& world_position : m_all_world_positions_in_range){
		new_world_positions_in_range.emplace_back(world_position + world_position_difference);
	}

	m_all_world_positions_in_range = new_world_positions_in_range;
	
}

std::vector<WorldPosition> VoxelInRangeUpdater::filter_to_non_loaded_new_world_positions() {

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