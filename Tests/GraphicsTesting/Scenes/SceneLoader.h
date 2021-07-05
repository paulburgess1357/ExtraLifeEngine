#pragma once
#include "../../ResourceManagement/IncludeResources.h"
#include "../../../Environment/Interfaces/Shader/IShaderProgram.h"
#include "entt/entity/registry.hpp"

class SceneLoader{
	
public:
	SceneLoader(ShaderResource& shader_resource, ModelResource& model_resource, 
		        TextureResource& texture_resource, LightResource& light_resource,
				CubeResource& cube_resource);
	void grid(entt::registry& registry);
	void single_cube(entt::registry& registry);	
	void single_cube_textured(entt::registry& registry);
	void single_model(entt::registry& registry);
	void cubemap(entt::registry& registry);
	void voxels(entt::registry& registry);
	void load_scene(entt::registry& registry);
	
private:
	void attach_scene_light(IShaderProgram& shader_program);
	void attach_dirlight(IShaderProgram& shader_program);
	void attach_point_light(IShaderProgram& shader_program);
	
	ShaderResource& m_shader_resource;
	ModelResource& m_model_resource;
	TextureResource& m_texture_resource;
	LightResource& m_light_resource;
	CubeResource& m_cube_resource;
};

