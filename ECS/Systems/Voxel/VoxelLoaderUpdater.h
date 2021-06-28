#pragma once
#include "../../Voxel/Neutral/WorldPosition.h"
#include <vector>
//TODO move this to World Folder

class VoxelLoaderUpdater{
	
public:
	static void initialize_all_world_positions_in_range();
	static void load_non_loaded_new_world_positions();
	
private:
	static std::vector<WorldPosition> get_non_loaded_new_world_positions();
	
};

