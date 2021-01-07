#pragma once
#include "../../../Environment/Interfaces/Shader/IShaderProgram.h"
#include "entt/entity/registry.hpp"

class SceneLoader{
	
public:
	static void grid(entt::registry& registry);
	static void single_cube(entt::registry& registry);	
	static void single_cube_textured(entt::registry& registry);
	static void single_model(entt::registry& registry);
	static void cubemap(entt::registry& registry);
	
private:
	static void attach_basic_lighting(std::shared_ptr<IShaderProgram>& shader_program);
};

