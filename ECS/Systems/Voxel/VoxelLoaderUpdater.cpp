#include "VoxelLoaderUpdater.h"
#include "../../ResourceManagement/VoxelResource.h"
#include "../../World/WorldPositionsInRangeUpdater.h"

void VoxelLoaderUpdater::initialize_all_world_positions_in_range(){
	const std::vector <WorldPosition> all_world_positions_in_range = WorldPositionsInRangeUpdater::get_all_world_positions_in_camera_range();
	VoxelResource::load_multiple_chunks(all_world_positions_in_range);
	VoxelResource::set_specific_chunk_neighbors(all_world_positions_in_range);
}

void VoxelLoaderUpdater::load_non_loaded_new_world_positions() {

	// Filter to only new world positions (no old chunks allowed!)
	const std::vector<WorldPosition> non_loaded_world_positions = get_non_loaded_new_world_positions();

	// Load new chunks into voxel resource
	VoxelResource::load_multiple_chunks(non_loaded_world_positions);

	// Update chunk neighbors for both brand new chunks and existing
	// old chunks that are adjacent to the new chunks
	VoxelResource::set_specific_chunk_neighbors(non_loaded_world_positions);
}

std::vector<WorldPosition> VoxelLoaderUpdater::get_non_loaded_new_world_positions() {
	
	//TODO Can this be made into returning only the new world positions?
	// NOTE: The initial run of this loads all voxels in range which is needed, otherwise you will only load the 'new' voxels, but technically all of them are new in the beginning.
	std::vector <WorldPosition> all_world_positions_in_range = WorldPositionsInRangeUpdater::get_new_world_positions_in_camera_range();
	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& chunkmap = VoxelResource::get_chunkmap();

	std::vector<WorldPosition> non_loaded_world_positions;
	for (const auto& world_position : all_world_positions_in_range) {
		if (chunkmap.count(world_position) == 0) {
			non_loaded_world_positions.emplace_back(world_position);
		}
	}

	return non_loaded_world_positions;
}