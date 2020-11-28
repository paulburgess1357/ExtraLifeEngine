#pragma once
#include "../../../../Camera/Camera.h"
#include "entt/entity/registry.hpp"

class IModelRenderer{

public:
	virtual ~IModelRenderer() = default;
	virtual void render(entt::registry& registry, Camera& camera) const = 0;
	static std::shared_ptr<IModelRenderer> get_model_renderer();
};

