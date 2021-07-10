#pragma once
#include "../../ResourceManagement/IncludeResources.h"
#include "../../../Environment/Interfaces/Framebuffer/IFrameBuffer.h"
#include "entt/entity/registry.hpp"

class SceneLoader{
	
public:
	SceneLoader(ShaderResource& shader_resource, ModelResource& model_resource, 
		        TextureResource& texture_resource, LightResource& light_resource,
				CubeResource& cube_resource, IFrameBuffer& framebuffer);
	void load_scene(entt::registry& registry);
	
private:
	void grid(entt::registry& registry);
	void single_cube(entt::registry& registry) const;
	void single_cube_textured(entt::registry& registry);
	void models(entt::registry& registry);
	void cubemap(entt::registry& registry);
	void voxels(entt::registry& registry);
	
	void load_backpack(entt::registry& registry);
	void load_troll(entt::registry& registry);
	void load_podracer(entt::registry& registry);
	void load_spartan(entt::registry& registry);
	void load_vivi(entt::registry& registry);
	void load_mech(entt::registry& registry);
	void load_cerberus(entt::registry& registry);
	void load_test_any_model(entt::registry& registry);

	void load_framebuffer(entt::registry& registry);
	
	ShaderResource& m_shader_resource;
	ModelResource& m_model_resource;
	TextureResource& m_texture_resource;
	LightResource& m_light_resource;
	CubeResource& m_cube_resource;
	IFrameBuffer& m_framebuffer;

};
