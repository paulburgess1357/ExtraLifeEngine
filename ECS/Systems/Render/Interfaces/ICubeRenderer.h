#pragma once
#include "../../../../Camera/Camera.h"
#include "entt/entity/registry.hpp"
#include <memory>

class ICubeRenderer{

public:
	virtual ~ICubeRenderer() = default;
	virtual void render(entt::registry& registry) const = 0;
	static std::shared_ptr<ICubeRenderer> get_cube_renderer();
	
};
