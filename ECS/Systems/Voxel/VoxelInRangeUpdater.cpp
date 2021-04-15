#include "VoxelInRangeUpdater.h"
#include "../../Voxel/Chunk/ChunkInRange.h"
#include "../../ResourceManagement/VoxelResource.h"
#include <iostream>

void VoxelInRangeUpdater::set_all_chunks_in_range(const Camera& camera){

	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& chunkmap = VoxelResource::get_chunkmap();

	//TODO REMOVE ME:
	
	// Set all chunks in range to false
	for(auto chunk : chunkmap){
		chunk.second->set_in_camera_range(false);				
	}

	// Create vector of chunk positions that are in range of the camera
	ChunkInRange::set_chunks_in_range(camera);
	std::vector<WorldPosition> chunks_in_range = ChunkInRange::get_chunks_in_range();

	// Iterate chunks in range vector and set to true
	//for(const auto chunk_position : chunks_in_range){
	//	auto chunk_iterator = chunkmap.find(chunk_position);		
	//	if(chunk_iterator != chunkmap.end()){
	//		std::cout << chunk_position.x << "," << chunk_position.y << "," << chunk_position.z << std::endl;
	//		chunk_iterator->second->set_in_camera_range(true);			
	//	}		
	//}

	for (const auto chunk_position : chunks_in_range) {

		if(chunkmap.count(chunk_position) > 0){
			//std::cout << chunk_position.x << "," << chunk_position.y << "," << chunk_position.z << std::endl;
			chunkmap[chunk_position]->set_in_camera_range(true);
		}
		
		//auto chunk_iterator = chunkmap.find(chunk_position);
		//if (chunk_iterator != chunkmap.end()) {
		// std::cout << chunk_position.x << "," << chunk_position.y << "," << chunk_position.z << std::endl;
		//	chunk_iterator->second->set_in_camera_range(true);
		//}
	}

	//std::cout << "--------------------------------------------" << std::endl;
	
}

