#pragma once
#include "entt/entity/registry.hpp"

class SceneLoader{
	
public:
	static void single_cube(entt::registry& registry);	
	static void single_cube_textured(entt::registry& registry);
};

