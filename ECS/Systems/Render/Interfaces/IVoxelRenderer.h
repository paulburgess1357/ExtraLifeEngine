#pragma once
#include "../../ResourceManagement/VoxelResource.h"
#include "../../World/WorldPositionsInRangeUpdater.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include "entt/entity/registry.hpp"
#include <memory>

class IVoxelRenderer{
	
public:
	IVoxelRenderer(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range, IShaderProgram& shader_program);
	virtual ~IVoxelRenderer() = default;
	virtual void render() const = 0;
	static std::unique_ptr<IVoxelRenderer> get_voxel_renderer(const VoxelResource& m_voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range, IShaderProgram& shader_program);

protected:
	const VoxelResource& m_voxel_resource;
	const WorldPositionsInRangeUpdater& m_world_positions_in_range_updater;
	IShaderProgram& m_voxel_shader_program;
};