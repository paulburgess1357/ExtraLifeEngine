#include "SceneLoader.h"

#include "../Cube/CubeResource.h"
#include "../../ResourceManagement/ShaderResource.h"
#include "../../ResourceManagement/TextureResource.h"
#include "../../ResourceManagement/LightResource.h"
#include "../../GraphicsTesting/Cube/CubeComponent.h"
#include "../../GraphicsTesting/Cube/TexturedCubeComponent.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"

#include "../../ECS/Components/Shader/ShaderComponent.h"
#include "../../ECS/Components/Transform/RotationComponent.h"
#include "../../ECS/Components/Transform/TransformComponent.h"

void SceneLoader::single_cube(entt::registry& registry) {

	std::shared_ptr<IShaderProgram> shader_program = ShaderResource::load("single_cube", "Assets/shaders/vertex/cube_colored.glsl", "Assets/shaders/fragment/cube_colored.glsl");

	DirectionalLight dirlight;
	dirlight.m_direction = glm::vec3(0.0f, 1.0f, 0.0f);
	LightResource::load("dirlight", dirlight);

	const SceneLight scenelight;
	LightResource::load("scenelight", scenelight);

	PointLight pointlight1;
	pointlight1.m_position = glm::vec3(0.0f, -1.0f, 0.0f);
	LightResource::load("pointlight1", pointlight1);

	PointLight pointlight2;
	pointlight2.m_position = glm::vec3(0.0f, 0.0f, -1.0f);
	LightResource::load("pointlight2", pointlight2);

	shader_program->attach_scene_light("scenelight");
	shader_program->attach_directional_light("dirlight");
	shader_program->attach_point_light("pointlight1");
	shader_program->attach_point_light("pointlight2");
	
	shader_program->set_uniform("material.diffuse", glm::vec3(0.5f, 0.9f, 0.31f));
	shader_program->set_uniform("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	shader_program->set_uniform("material.shininess", 32.0f);

	CubeComponent cube_component{ CubeResource::get("cube_normal") };
	const entt::entity cube_entity = registry.create();

	registry.emplace<ShaderComponent>(cube_entity, shader_program);
	registry.emplace<CubeComponent>(cube_entity, cube_component);
	registry.emplace<TransformComponent>(cube_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
	registry.emplace<RotationComponent>(cube_entity, 0.0f, 0.2f, 0.0f, 0.0f);

}

void SceneLoader::single_cube_textured(entt::registry& registry) {

	std::shared_ptr<IShaderProgram> shader_program = ShaderResource::load("single_cube_textured", "Assets/shaders/vertex/cube_textured.glsl", "Assets/shaders/fragment/cube_textured.glsl");
	TextureResource::load("brown_container", "Assets/textures/crate.jpg", true);
	TextureResource::load("brown_container_boarder", "Assets/textures/container_specular_map.png", true);

	DirectionalLight dirlight;
	dirlight.m_direction = glm::vec3(0.0f, 1.0f, 0.0f);
	LightResource::load("dirlight", dirlight);

	const SceneLight scenelight;	
	LightResource::load("scenelight", scenelight);

	PointLight pointlight1;
	pointlight1.m_position = glm::vec3(3.0f, -1.0f, 0.0f);
	LightResource::load("pointlight1", pointlight1);

	PointLight pointlight2;
	pointlight2.m_position = glm::vec3(3.0f, 0.0f, -1.0f);
	LightResource::load("pointlight2", pointlight2);	

	shader_program->attach_diffuse_texture("brown_container");
	shader_program->attach_specular_texture("brown_container_boarder", 32.0f);

	shader_program->attach_scene_light("scenelight");
	shader_program->attach_directional_light("dirlight");
	shader_program->attach_point_light("pointlight1");
	shader_program->attach_point_light("pointlight2");

	const entt::entity textured_cube_entity = registry.create();
	TexturedCubeComponent textured_cube_component{ CubeResource::get("cube_normal_textured") };
	registry.emplace<ShaderComponent>(textured_cube_entity, shader_program);
	registry.emplace<TexturedCubeComponent>(textured_cube_entity, textured_cube_component);
	registry.emplace<TransformComponent>(textured_cube_entity, glm::vec3{ 3.0f, 0.0f, 0.0f });
	registry.emplace<RotationComponent>(textured_cube_entity, 0.0f, -0.2f, 0.0f, 0.0f);
}



