#pragma once
#include "../../World/WorldPosition.h"
#include "../../ResourceManagement/VoxelResource.h"
#include <vector>

class VoxelLoader{
	
public:
	VoxelLoader(VoxelResource& voxel_resource);
	void initialize_all_world_positions_in_range() const;
	void update() const;	
	
private:
	void load_non_loaded_new_world_positions() const;
	void unload_vbo_vao_not_in_range() const;
	void load_vbo_vao_new_in_range() const;
	[[nodiscard]] std::vector<WorldPosition> get_non_loaded_new_world_positions() const;

	VoxelResource& m_voxel_resource;
		
};
