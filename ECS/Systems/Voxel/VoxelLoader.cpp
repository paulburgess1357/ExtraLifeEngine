#include "VoxelLoader.h"
#include "../../ResourceManagement/VoxelResource.h"
#include "../../World/WorldPositionsInRangeUpdater.h"

void VoxelLoader::initialize_all_world_positions_in_range(){
	const std::vector <WorldPosition> all_world_positions_in_range = WorldPositionsInRangeUpdater::get_all_world_positions_in_camera_range();
	VoxelResource::load_multiple_chunks(all_world_positions_in_range);
	VoxelResource::set_specific_chunk_neighbors(all_world_positions_in_range);
}

void VoxelLoader::update(){
	if(WorldPositionsInRangeUpdater::has_camera_chunk_changed()){
		unload_vbo_vao_not_in_range();
		load_non_loaded_new_world_positions();
		load_vbo_vao_new_in_range();
	}	
}

void VoxelLoader::unload_vbo_vao_not_in_range() {
	std::vector<WorldPosition> out_of_range_world_positions = WorldPositionsInRangeUpdater::get_old_world_positions_not_in_camera_range();
	for (const auto& world_position : out_of_range_world_positions) {
		VoxelResource::unload_vbo_vao_into_pool(world_position);
	}
}

void VoxelLoader::load_non_loaded_new_world_positions() {

	// Filter to only new world positions (no old chunks allowed!)
	const std::vector<WorldPosition> non_loaded_world_positions = get_non_loaded_new_world_positions();

	// Load new chunks into voxel resource
	VoxelResource::load_multiple_chunks(non_loaded_world_positions);

	// Update chunk neighbors for both brand new chunks and existing
	// old chunks that are adjacent to the new chunks
	VoxelResource::set_specific_chunk_neighbors(non_loaded_world_positions);
	
}

void VoxelLoader::load_vbo_vao_new_in_range() {

	std::vector <WorldPosition> all_new_world_positions_in_range = WorldPositionsInRangeUpdater::get_new_world_positions_in_camera_range();
	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& chunkmap = VoxelResource::get_chunkmap();

	for (const auto& world_position : all_new_world_positions_in_range) {
		std::shared_ptr<Chunk> chunk = chunkmap[world_position];

		if (!chunk->vbo_vao_initialized()) {
			VoxelResource::load_vbo_vao_into_chunk(world_position);
			chunk->set_update_required(true);
		}

	}

}

std::vector<WorldPosition> VoxelLoader::get_non_loaded_new_world_positions() {

	std::vector <WorldPosition> all_new_world_positions_in_range = WorldPositionsInRangeUpdater::get_new_world_positions_in_camera_range();
	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& chunkmap = VoxelResource::get_chunkmap();

	std::vector<WorldPosition> non_loaded_world_positions;
	for (const auto& world_position : all_new_world_positions_in_range) {
		if (chunkmap.count(world_position) == 0) {
			non_loaded_world_positions.emplace_back(world_position);
		}
	}

	return non_loaded_world_positions;
}
