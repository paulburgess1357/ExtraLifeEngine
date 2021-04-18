#include "VoxelInRangeUpdater.h"
#include "../../Voxel/Chunk/ChunkInRange.h"
#include "../../ResourceManagement/VoxelResource.h"
#include <iostream>

void VoxelInRangeUpdater::set_all_chunks_in_range(const Camera& camera){

	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& chunkmap = VoxelResource::get_chunkmap();
	
	// Set all chunks in range to false
	for(auto chunk : chunkmap){
		chunk.second->set_in_camera_range(false);				
	}

	// Create vector of chunk positions that are in range of the camera
	ChunkInRange::set_chunks_in_range(camera);
	std::vector<WorldPosition> chunks_in_range = ChunkInRange::get_chunks_in_range();

	for (const auto chunk_position : chunks_in_range) {
		if(chunkmap.count(chunk_position) > 0){
			chunkmap[chunk_position]->set_in_camera_range(true);
		}
	}	
}

