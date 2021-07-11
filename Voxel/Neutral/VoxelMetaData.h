#pragma once
#include <string>

struct VoxelMetaData{

	VoxelMetaData() = default;
	VoxelMetaData(std::string voxel_shader, const int x_range, const int y_range, const int z_range)
		:m_voxel_shader(std::move(voxel_shader)),
		m_voxel_x_range{ x_range },
		m_voxel_y_range{ y_range },
		m_voxel_z_range{ z_range }{
	}

	std::string m_voxel_shader = "No Voxel Shader Selected";
	int m_voxel_x_range = 0;
	int m_voxel_y_range = 0;
	int m_voxel_z_range = 0;
};
