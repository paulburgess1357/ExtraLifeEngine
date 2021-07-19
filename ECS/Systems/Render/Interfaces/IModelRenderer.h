#pragma once
#include "entt/entity/registry.hpp"
#include "../../../../Camera/Camera.h"
#include <memory>

class IModelRenderer{

public:
	virtual ~IModelRenderer() = default;
	virtual void render(entt::registry& registry, Camera& camera) const = 0;
	static std::unique_ptr<IModelRenderer> get_model_renderer();
	
};
