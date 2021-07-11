#pragma once
#include "../../Voxel/Neutral/VoxelMetaData.h"
#include "../../ResourceManagement/VoxelResource.h"
#include "../../ResourceManagement/ShaderResource.h"
#include "../../World/WorldPositionsInRangeUpdater.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include "entt/entity/registry.hpp"
#include <memory>

class IVoxelRenderer{
	
public:
	IVoxelRenderer(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range, IShaderProgram* shader_program);
	virtual ~IVoxelRenderer() = default;
	virtual void render() const = 0;
	static std::unique_ptr<IVoxelRenderer> get_voxel_renderer(const VoxelResource& voxel_resource, const WorldPositionsInRangeUpdater& world_positions_in_range, ShaderResource& shader_resource, const VoxelMetaData& voxel_meta_data);

protected:
	const VoxelResource& m_voxel_resource;
	const WorldPositionsInRangeUpdater& m_world_positions_in_range_updater;
	IShaderProgram* m_voxel_shader_program;

	private:
		static void run_shader_ptr_checks(const WorldPositionsInRangeUpdater& world_positions_in_range, IShaderProgram* shader_program);
};
