#pragma once
#include "../../World/WorldPosition.h"
#include <vector>
//TODO move this to World Folder

class VoxelLoader{
	
public:
	static void initialize_all_world_positions_in_range();
	static void load_non_loaded_new_world_positions();
	static void unload_vbo_vao_not_in_range();
	static void load_vbo_vao_new_in_range();
	
private:
	static std::vector<WorldPosition> get_non_loaded_new_world_positions();
	
};
