#include "VoxelInRangeUpdater.h"
#include "../../Voxel/Chunk/ChunkInRange.h"
#include "../../ResourceManagement/VoxelResource.h"
#include <iostream>

void VoxelInRangeUpdater::set_all_chunks_in_range(const Camera& camera, const int range){

	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash>& chunkmap = VoxelResource::get_chunkmap();
	
	// Set all chunks in range to false
	for(auto chunk : chunkmap){
		chunk.second->set_in_camera_range(false);				
	}

	std::vector<std::shared_ptr<Chunk>> nearby_chunks = ChunkInRange::get_chunks_in_range(camera, range);

	for(auto & chunk : nearby_chunks){
		chunk->set_in_camera_range(true);
	}

}

