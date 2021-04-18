#include "ChunkInRange.h"

#include <algorithm>

#include "Chunk.h"
#include <glm/glm.hpp>
#include <iostream>

int ChunkInRange::m_range_qty = 16;
std::vector<WorldPosition> ChunkInRange::m_chunks_in_camera_range;

void ChunkInRange::set_chunks_in_range(const Camera& camera) {

	const glm::vec3 camera_position = camera.get_camera_position();

	const int nearest_x_chunk = static_cast<int>(camera_position.x) / x_block_qty * x_block_qty;
	const int nearest_y_chunk = static_cast<int>(camera_position.y) / y_block_qty * y_block_qty;
	const int nearest_z_chunk = static_cast<int>(camera_position.z) / z_block_qty * z_block_qty;
	
	

	const WorldPosition base_position{nearest_x_chunk, nearest_y_chunk, nearest_z_chunk};
	
	//std::cout << "base position: " << base_position.x << "," << base_position.y << "," << base_position.z << std::endl;
	m_chunks_in_camera_range = get_chunks_in_range(base_position); //TODO Make const

	//m_chunks_in_camera_range = chunks_in_range;
	//std::sort(chunks_in_range.begin(), chunks_in_range.end(), less_than_key_REMOVE_ME());
	//TODO Remove when complete.  Temp dupe check
	
	//for(int i = 0; i < chunks_in_range.size(); i++){

	//	WorldPosition check1 = chunks_in_range.at(i);

	//	for(int j = i + 1; j < chunks_in_range.size(); j++){

	//		WorldPosition check2 = chunks_in_range.at(j);

	//		if((check1.x == check2.x) && (check1.y == check2.y) && (check1.z == check2.z)){
	//			
	//			std::cout << "DUPLICATE FOUND" << std::endl;
	//		}

	//		
	//	}
	//	
	//}
			
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

	// Load base position
	chunks_in_range.emplace_back(base_position.x, base_position.y, base_position.z);

	int range_qty_loop = m_range_qty + 1;
	for(int x = 0; x < range_qty_loop; x++){
		for(int y = 0; y < range_qty_loop; y++){
			for(int z = 0; z < range_qty_loop; z++){
				
				chunks_in_range.emplace_back(base_position.x + (x_block_qty * x), base_position.y + (y_block_qty * y), base_position.z + (z_block_qty * z));

				chunks_in_range.emplace_back(base_position.x + (x_block_qty * x), base_position.y - (y_block_qty * y), base_position.z - (z_block_qty * z));
				chunks_in_range.emplace_back(base_position.x - (x_block_qty * x), base_position.y + (y_block_qty * y), base_position.z - (z_block_qty * z));
				chunks_in_range.emplace_back(base_position.x - (x_block_qty * x), base_position.y - (y_block_qty * y), base_position.z + (z_block_qty * z));

				chunks_in_range.emplace_back(base_position.x - (x_block_qty * x), base_position.y + (y_block_qty * y), base_position.z + (z_block_qty * z));
				chunks_in_range.emplace_back(base_position.x + (x_block_qty * x), base_position.y - (y_block_qty * y), base_position.z + (z_block_qty * z));
				chunks_in_range.emplace_back(base_position.x + (x_block_qty * x), base_position.y + (y_block_qty * y), base_position.z - (z_block_qty * z));

				chunks_in_range.emplace_back(base_position.x - (x_block_qty * x), base_position.y - (y_block_qty * y), base_position.z - (z_block_qty * z));												
			}
		}
	}
	
	//for(int x = 1; x <= m_range_qty; x++){
	//	const int x_amt = x * x_block_qty;		
	//	for(int y = 1; y <= m_range_qty; y++){
	//		const int y_amt = y * y_block_qty;			
	//		for(int z = 1; z <= m_range_qty; z++){
	//			const int z_amt = z * z_block_qty;

	//			// Load X Range Chunks
	//			chunks_in_range.emplace_back(base_position.x + x_amt, base_position.y, base_position.z);
	//			chunks_in_range.emplace_back(base_position.x - x_amt, base_position.y, base_position.z);

	//			// Load X & Y Range Chunks
	//			chunks_in_range.emplace_back(base_position.x + x_amt, base_position.y + y_amt, base_position.z);
	//			chunks_in_range.emplace_back(base_position.x - x_amt, base_position.y - y_amt, base_position.z);

	//			chunks_in_range.emplace_back(base_position.x + x_amt, base_position.y - y_amt, base_position.z);
	//			chunks_in_range.emplace_back(base_position.x - x_amt, base_position.y + y_amt, base_position.z);

	//			// Load X & Z Range Chunks
	//			chunks_in_range.emplace_back(base_position.x + x_amt, base_position.y, base_position.z + z_amt);
	//			chunks_in_range.emplace_back(base_position.x - x_amt, base_position.y, base_position.z - z_amt);

	//			chunks_in_range.emplace_back(base_position.x + x_amt, base_position.y, base_position.z - z_amt);
	//			chunks_in_range.emplace_back(base_position.x - x_amt, base_position.y, base_position.z + z_amt);

	//			// Load Y Range Chunks
	//			chunks_in_range.emplace_back(base_position.x, base_position.y + y_amt, base_position.z);
	//			chunks_in_range.emplace_back(base_position.x, base_position.y - y_amt, base_position.z);

	//			// Load Y & Z Range Chunks
	//			chunks_in_range.emplace_back(base_position.x, base_position.y + y_amt, base_position.z + z_amt);
	//			chunks_in_range.emplace_back(base_position.x, base_position.y - y_amt, base_position.z - z_amt);

	//			chunks_in_range.emplace_back(base_position.x, base_position.y + y_amt, base_position.z - z_amt);
	//			chunks_in_range.emplace_back(base_position.x, base_position.y - y_amt, base_position.z + z_amt);

	//			// Load Z Range Chunks
	//			chunks_in_range.emplace_back(base_position.x, base_position.y, base_position.z + z_amt);
	//			chunks_in_range.emplace_back(base_position.x, base_position.y, base_position.z - z_amt);
	//			
	//		}			
	//	}		
	//}
				
	return chunks_in_range;
	
}

std::vector<WorldPosition> ChunkInRange::get_chunks_in_range(){
	return m_chunks_in_camera_range;
}