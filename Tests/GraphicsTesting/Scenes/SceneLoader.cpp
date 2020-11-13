#include "SceneLoader.h"
#include "../Cube/CubeResource.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include "../../ResourceManagement/ShaderResource.h"
#include "../../ECS/Components/Shader/ShaderComponent.h"
#include "../../ECS/Components/Transform/TransformComponent.h"
#include "../../ECS/Components/Transform/MovementVelocityComponent.h"
#include "../../GraphicsTesting/Cube/CubeComponent.h"

void SceneLoader::single_cube(entt::registry& registry){

	std::shared_ptr<IShaderProgram> shader_program = ShaderResource::load("cube_test", "Assets/shaders/vertex/cube.glsl", "Assets/shaders/fragment/cube.glsl");
	CubeComponent cube_component{ CubeResource::get("cube") };
	
	const entt::entity cube_entity = registry.create();
	registry.emplace<ShaderComponent>(cube_entity, shader_program);
	registry.emplace<CubeComponent>(cube_entity, cube_component);
	registry.emplace<TransformComponent>(cube_entity, glm::vec3{ 0.0f, 0.0f, 0.00f });
	registry.emplace<MovementVelocityComponent>(cube_entity, glm::vec3{ 0.0f, 0.00f, 0.00f });
	
}