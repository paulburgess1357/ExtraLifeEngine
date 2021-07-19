#pragma once
#include "../../ResourceManagement/IncludeResources.h"
#include "../../Voxel/Neutral/VoxelMetaData.h"
#include "../../Environment/Neutral/FrameBuffer/FrameBufferHandler.h"
#include "entt/entity/registry.hpp"


class SceneLoader{
	
public:
	SceneLoader(ShaderResource& shader_resource, ModelResource& model_resource, 
		        TextureResource& texture_resource, LightResource& light_resource,
				CubeResource& cube_resource);
	void load_scene(entt::registry& registry);
	[[nodiscard]] VoxelMetaData get_voxel_metadata() const;
	
private:

	// Shading Book
	void single_cube_diffuse_lighting(entt::registry& registry) const;





	
	
	void single_cube(entt::registry& registry) const;		
	void cubemap(entt::registry& registry) const;
	void grid(entt::registry& registry) const;
	void single_cube_textured(entt::registry& registry) const;

	void voxels(entt::registry& registry, const int x_range, const int y_range, const int z_range);
	void load_backpack(entt::registry& registry) const;
	void load_spartan(entt::registry& registry) const;
	//void load_standard_framebuffer(entt::registry& registry) const;
	//void load_hdr_framebuffer(entt::registry& registry) const;
	
	ShaderResource& m_shader_resource;
	ModelResource& m_model_resource;
	TextureResource& m_texture_resource;
	LightResource& m_light_resource;
	CubeResource& m_cube_resource;

	VoxelMetaData m_voxel_range_data;
};
