#include "VoxelInRangeUpdater.h"
#include "../../Voxel/Chunk/ChunkInRange.h"
#include "../../ResourceManagement/VoxelResource.h"
#include "../../ResourceManagement/ShaderResource.h"
#include "../../ECS/Components/Voxel/ChunkComponent.h"
#include "../../ECS/Components/Transform/TransformComponent.h"
#include <iostream>

WorldPosition VoxelInRangeUpdater::m_camera_chunk_coords{ -99, -99, -99 };
std::vector<WorldPosition> VoxelInRangeUpdater::m_chunks_in_range;

std::vector<WorldPosition> VoxelInRangeUpdater::get_chunks_in_range(){
	return m_chunks_in_range;
}

void VoxelInRangeUpdater::load_in_range_chunks(const Camera& camera, entt::registry& registry, const int x_range, const int y_range, const int z_range) {

	const WorldPosition camera_chunk_coords = get_nearest_chunk_coords_to_camera(camera);	

	// Only update 'chunks in range' if the camera position has changed
	if (m_camera_chunk_coords != camera_chunk_coords) {		
		m_camera_chunk_coords = camera_chunk_coords;

		// Get a 'sphere' of chunks in range and set to in camera range
		std::vector<WorldPosition> world_positions_in_range = ChunkInRange::get_world_positions_in_range(m_camera_chunk_coords, x_range, y_range, z_range);

		// Filter to only new world positions (no old chunks allowed!)
		std::vector<WorldPosition> new_world_positions_in_range = filter_to_new_world_positions(world_positions_in_range);

		// Load new chunks into ecs and voxel resource
		load_new_chunks_in_range(new_world_positions_in_range);

		// Update chunk neighbors for both brand new chunks and existing
		// old chunks that are adjacent to the new chunks
		VoxelResource::set_specific_chunk_neighbors(new_world_positions_in_range);
		m_chunks_in_range = world_positions_in_range;
	}	
}

WorldPosition VoxelInRangeUpdater::get_nearest_chunk_coords_to_camera(const Camera& camera){	
	const glm::vec3 camera_position = camera.get_camera_position();

	const int nearest_x_chunk = static_cast<int>(camera_position.x) / x_block_qty * x_block_qty;
	const int nearest_y_chunk = static_cast<int>(camera_position.y) / y_block_qty * y_block_qty;
	const int nearest_z_chunk = static_cast<int>(camera_position.z) / z_block_qty * z_block_qty;

	const WorldPosition new_camera_position = WorldPosition{ nearest_x_chunk, nearest_y_chunk, nearest_z_chunk };
	return new_camera_position;
}

std::vector<WorldPosition> VoxelInRangeUpdater::filter_to_new_world_positions(std::vector<WorldPosition>& chunks_in_range){

	std::vector<WorldPosition> newchunks_positions;
	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& chunkmap = VoxelResource::get_chunkmap();
	
	for (const auto& world_position : chunks_in_range) {
		if (chunkmap.count(world_position) == 0) {
			newchunks_positions.emplace_back(world_position);
		}
	}

	return newchunks_positions;	
}

void VoxelInRangeUpdater::load_new_chunks_in_range(std::vector<WorldPosition>& chunks_in_range) {
	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& chunkmap = VoxelResource::get_chunkmap();
	for (const auto& world_position : chunks_in_range) {
		VoxelResource::load_individual_chunk(world_position);
	}
}