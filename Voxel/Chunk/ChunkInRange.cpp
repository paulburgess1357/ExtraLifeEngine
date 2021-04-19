#include "ChunkInRange.h"
#include "Chunk.h"
#include "../../ResourceManagement/VoxelResource.h"
#include <glm/glm.hpp>
#include <iostream>

WorldPosition ChunkInRange::m_camera_chunk_coords {-99, -99, -99};
std::vector<std::shared_ptr<Chunk>> ChunkInRange::m_chunks_in_camera_range;

std::vector<std::shared_ptr<Chunk>> ChunkInRange::get_chunks_in_range(const Camera& camera, const int range) {

	const WorldPosition new_camera_chunk_coords = get_nearest_chunk_coords_to_camera(camera);
	if(new_camera_chunk_coords != m_camera_chunk_coords){
		std::cout << "new camera position" << std::endl;
		m_camera_chunk_coords = new_camera_chunk_coords;
		load_chunks_in_range(m_camera_chunk_coords, range);
	}
			
	return m_chunks_in_camera_range;
}

WorldPosition ChunkInRange::get_nearest_chunk_coords_to_camera(const Camera& camera) {

	const glm::vec3 camera_position = camera.get_camera_position();

	const int nearest_x_chunk = static_cast<int>(camera_position.x) / x_block_qty * x_block_qty;
	const int nearest_y_chunk = static_cast<int>(camera_position.y) / y_block_qty * y_block_qty;
	const int nearest_z_chunk = static_cast<int>(camera_position.z) / z_block_qty * z_block_qty;
		
	WorldPosition new_camera_position = WorldPosition {nearest_x_chunk, nearest_y_chunk, nearest_z_chunk};
	return new_camera_position;
	
}

void ChunkInRange::load_chunks_in_range(const WorldPosition& base_position, const int range){
	const std::vector<WorldPosition> world_positions{ get_world_positions_in_range(base_position, range) };
	fill_chunks_in_camera_range(world_positions);	
}

std::vector<WorldPosition> ChunkInRange::get_world_positions_in_range(const WorldPosition& base_position, const int range){
	std::vector<WorldPosition> world_positions_in_range;
	
	const int range_qty_start = range * -1;
	const int range_qty_end = range + 1;

	for (int x = range_qty_start; x < range_qty_end; x++) {
		for (int y = range_qty_start; y < range_qty_end; y++) {
			for (int z = range_qty_start; z < range_qty_end; z++) {
				world_positions_in_range.emplace_back(base_position.x + (x_block_qty * x), base_position.y + (y_block_qty * y), base_position.z + (z_block_qty * z));
			}
		}
	}
	return world_positions_in_range;
}

void ChunkInRange::fill_chunks_in_camera_range(const std::vector<WorldPosition>& world_positions_in_range){

	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& chunkmap = VoxelResource::get_chunkmap();
	
	// Filter all possible chunks to be those that actually exist
	std::vector<std::shared_ptr<Chunk>> filtered_chunks_in_range;
	for (const auto chunk_position : world_positions_in_range) {
		if (chunkmap.count(chunk_position) > 0) {
			filtered_chunks_in_range.push_back(chunkmap[chunk_position]);
		}
	}

	m_chunks_in_camera_range = filtered_chunks_in_range;	
}