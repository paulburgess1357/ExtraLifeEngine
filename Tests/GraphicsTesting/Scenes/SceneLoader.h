#pragma once
#include "entt/entity/registry.hpp"

class SceneLoader{
	
public:
	static void single_cube(entt::registry& registry);	
	static void single_cube_textured(entt::registry& registry);
	static void single_cube_lighting(entt::registry& registry);
	static void single_cube_textured_lighting_maps(entt::registry& registry);
	static void single_cube_textured_lighting_maps_directional_lights(entt::registry& registry);
	static void single_cube_textured_lighting_maps_directional_lights_using_attach(entt::registry& registry);
};

