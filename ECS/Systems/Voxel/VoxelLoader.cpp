#include "VoxelLoader.h"
#include "../../World/WorldPositionsInRangeUpdater.h"

VoxelLoader::VoxelLoader(VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range)
	:m_voxel_resource{ voxel_resource },
	m_world_positions_in_range{ world_positions_in_range }{
	load_initial_all_world_positions_in_range();
}

void VoxelLoader::load_initial_all_world_positions_in_range() const{
	const std::vector <WorldPosition>& all_world_positions_in_range = m_world_positions_in_range.get_all_world_positions_in_camera_range();
	m_voxel_resource.load_multiple_chunks(all_world_positions_in_range);
	m_voxel_resource.set_specific_chunk_neighbors(all_world_positions_in_range);
}

void VoxelLoader::update() const{
	if(m_world_positions_in_range.has_camera_chunk_changed()){
		unload_vbo_vao_not_in_range();
		load_non_loaded_new_world_positions();
		load_vbo_vao_new_in_range();
	}	
}

void VoxelLoader::unload_vbo_vao_not_in_range() const {
	const std::vector<WorldPosition>& out_of_range_world_positions = m_world_positions_in_range.get_old_world_positions_not_in_camera_range();
	for (const auto& world_position : out_of_range_world_positions) {
		m_voxel_resource.unload_vbo_vao_into_pool(world_position);
	}
}

void VoxelLoader::load_non_loaded_new_world_positions() const {

	// Filter to only new world positions (no old chunks allowed!)
	const std::vector<WorldPosition> non_loaded_world_positions = get_non_loaded_new_world_positions();

	// Load new chunks into voxel resource
	m_voxel_resource.load_multiple_chunks(non_loaded_world_positions);

	// Update chunk neighbors for both brand new chunks and existing
	// old chunks that are adjacent to the new chunks
	m_voxel_resource.set_specific_chunk_neighbors(non_loaded_world_positions);
	
}

void VoxelLoader::load_vbo_vao_new_in_range() const {

	const std::vector <WorldPosition>& all_new_world_positions_in_range = m_world_positions_in_range.get_new_world_positions_in_camera_range();
	for (const auto& world_position : all_new_world_positions_in_range) {
		Chunk* chunk = m_voxel_resource.get_chunk(world_position);

		if (!chunk->vbo_vao_initialized()) {
			m_voxel_resource.load_vbo_vao_into_chunk(world_position);
			chunk->set_update_required(true);
		}

	}

}

std::vector<WorldPosition> VoxelLoader::get_non_loaded_new_world_positions() const {

	const std::vector <WorldPosition>& all_new_world_positions_in_range = m_world_positions_in_range.get_new_world_positions_in_camera_range();
	std::vector<WorldPosition> non_loaded_world_positions;
	
	for (const auto& world_position : all_new_world_positions_in_range) {
		if (!m_voxel_resource.is_world_position_loaded(world_position)) {
			non_loaded_world_positions.emplace_back(world_position);
		}
	}

	return non_loaded_world_positions;
}
