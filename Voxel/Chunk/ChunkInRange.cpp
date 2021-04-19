#include "ChunkInRange.h"
#include "Chunk.h"
#include <glm/glm.hpp>
#include <iostream>

int ChunkInRange::m_range_qty = 10;
WorldPosition ChunkInRange::m_camera_position;
std::vector<WorldPosition> ChunkInRange::m_chunks_in_camera_range;

void ChunkInRange::set_chunks_in_range(const Camera& camera) {

	const glm::vec3 camera_position = camera.get_camera_position();

	const int nearest_x_chunk = static_cast<int>(camera_position.x) / x_block_qty * x_block_qty;
	const int nearest_y_chunk = static_cast<int>(camera_position.y) / y_block_qty * y_block_qty;
	const int nearest_z_chunk = static_cast<int>(camera_position.z) / z_block_qty * z_block_qty;
		
	WorldPosition new_camera_position = WorldPosition {nearest_x_chunk, nearest_y_chunk, nearest_z_chunk};

	// Update chunks in range only if camera is at a new chunk
	if(m_camera_position != new_camera_position){
		std::cout << "updating camera position" << std::endl;
		m_camera_position = new_camera_position;
		m_chunks_in_camera_range = get_chunks_in_range(m_camera_position);
	}
	
}

std::vector<WorldPosition> ChunkInRange::get_chunks_in_range(const WorldPosition& base_position){

	// m_range_qty is how many chunks you want to be considered in range.

	// E.g. Camera position = 0,0,0 & m_range_qty = 1
	// Chunks in range (x only): (-32, 0, 0) & (32, 0, 0)
	//
	// E.g.2 Camera position = 0,0,0 & m_range_qty = 3
	// // Chunks in range (x only): (-32, 0, 0), (-64, 0, 0), (-96, 0, 0)
	//                            & ( 32, 0, 0), ( 64, 0, 0), ( 96, 0, 0)

	std::vector<WorldPosition> chunks_in_range;

	const int range_qty_loop = m_range_qty + 1;
	const int range_qty_start = m_range_qty * -1;
	
	for (int x = range_qty_start; x < range_qty_loop; x++) {
		for (int y = range_qty_start; y < range_qty_loop; y++) {
			for (int z = range_qty_start; z < range_qty_loop; z++) {
				chunks_in_range.emplace_back(base_position.x + (x_block_qty * x), base_position.y + (y_block_qty * y), base_position.z + (z_block_qty * z));
			}
		}
	}
				
	return chunks_in_range;
	
}

std::vector<WorldPosition> ChunkInRange::get_chunks_in_range(){
	return m_chunks_in_camera_range;
}