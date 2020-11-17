#include "SceneLoader.h"

#include "../Cube/CubeResource.h"
#include "../../ResourceManagement/ShaderResource.h"
#include "../../ResourceManagement/TextureResource.h"
#include "../../GraphicsTesting/Cube/CubeComponent.h"
#include "../../GraphicsTesting/Cube/TexturedCubeComponent.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"

#include "../../ECS/Components/Shader/ShaderComponent.h"
#include "../../ECS/Components/Transform/ScaleComponent.h"
#include "../../ECS/Components/Transform/RotationComponent.h"
#include "../../ECS/Components/Transform/TransformComponent.h"
#include "../../ECS/Components/Transform/MovementVelocityComponent.h"

void SceneLoader::single_cube(entt::registry& registry) {

	std::shared_ptr<IShaderProgram> shader_program = ShaderResource::load("cube_test", "Assets/shaders/vertex/cube_colored.glsl", "Assets/shaders/fragment/cube_colored.glsl");
	shader_program->set_uniform("cube_color", glm::vec3(0.4f, 0.1f, 0.9f));

	CubeComponent cube_component{ CubeResource::get("cube") };
	const entt::entity cube_entity = registry.create();

	registry.emplace<ShaderComponent>(cube_entity, shader_program);
	registry.emplace<CubeComponent>(cube_entity, cube_component);
	registry.emplace<TransformComponent>(cube_entity, glm::vec3{ 0.0f, 0.0f, 0.00f });
	registry.emplace<RotationComponent>(cube_entity, 0.0f, 0.2f, 0.0f, 0.0f);

}

void SceneLoader::single_cube_textured(entt::registry& registry) {

	TextureResource::load("texture1", "Assets/textures/colorful_squares.jpg", true);

	std::shared_ptr<IShaderProgram> shader_program = ShaderResource::load("textured_cube_test", "Assets/shaders/vertex/textured_cube.glsl", "Assets/shaders/fragment/textured_cube.glsl");
	shader_program->attach_texture("texture1");

	TexturedCubeComponent textured_cube_component{ CubeResource::get("cube_textured") };

	const entt::entity textured_cube_entity = registry.create();
	registry.emplace<ShaderComponent>(textured_cube_entity, shader_program);
	registry.emplace<TexturedCubeComponent>(textured_cube_entity, textured_cube_component);
	registry.emplace<TransformComponent>(textured_cube_entity, glm::vec3{ 0.0f, 2.0f, 0.00f });
	registry.emplace<RotationComponent>(textured_cube_entity, 0.0f, -0.2f, 0.0f, 0.0f);

}

void SceneLoader::single_cube_lighting(entt::registry& registry) {

	std::shared_ptr<IShaderProgram> shader_program = ShaderResource::load("cube_test", "Assets/shaders/vertex/cube_colored_lighting.glsl", "Assets/shaders/fragment/cube_colored_lighting.glsl");
	shader_program->set_uniform("cube_color", glm::vec3(0.4f, 0.1f, 0.9f));
	shader_program->set_uniform("light_color", glm::vec3(1.0f, 1.0f, 1.0f));
	shader_program->set_uniform("light_world_position", glm::vec3(1.0f, 1.0f, 0.0f));

	CubeComponent cube_component{ CubeResource::get("cube_normal") };
	const entt::entity cube_entity = registry.create();

	registry.emplace<ShaderComponent>(cube_entity, shader_program);
	registry.emplace<CubeComponent>(cube_entity, cube_component);
	registry.emplace<TransformComponent>(cube_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
	registry.emplace<RotationComponent>(cube_entity, 0.0f, 0.2f, 0.0f, 0.0f);

}
