#pragma once
#include "../../ResourceManagement/IncludeResources.h"
#include "../../../Environment/Interfaces/Framebuffer/IFrameBuffer.h"
#include "entt/entity/registry.hpp"

class SceneLoader{
	
public:
	SceneLoader(ShaderResource& shader_resource, ModelResource& model_resource, 
		        TextureResource& texture_resource, LightResource& light_resource,
				CubeResource& cube_resource, IFrameBuffer& framebuffer);
	void load_scene(entt::registry& registry) const;
	
private:
	void cubemap(entt::registry& registry) const;
	void grid(entt::registry& registry) const;
	void single_cube(entt::registry& registry) const;
	void single_cube_textured(entt::registry& registry) const;

	// void voxels(entt::registry& registry);
	void load_backpack(entt::registry& registry) const;
	void load_spartan(entt::registry& registry) const;
	void load_framebuffer(entt::registry& registry) const;
	
	ShaderResource& m_shader_resource;
	ModelResource& m_model_resource;
	TextureResource& m_texture_resource;
	LightResource& m_light_resource;
	CubeResource& m_cube_resource;
	IFrameBuffer& m_framebuffer;

};
