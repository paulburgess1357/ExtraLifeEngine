#include "SceneLoader.h"
#include "../../ECS/Components/IncludeComponents.h"
#include "../../ResourceManagement/IncludeResources.h"
#include "../../../Utility/FatalError.h"

// Shaders

// Model Shaders
	// Standard model shaders assume diffuse and specular textures
	// TBN model shaders assume diffuse, normal, and specular textures
	
	// Standard model shader: Assets/shaders/vertex/model.glsl; Assets/shaders/fragment/model.glsl
	// TBN model shader (conversion in vertex (bad)): Assets/shaders/vertex/model_normals_TBN_vertex.glsl; Assets/shaders/fragment/model_normals_TBN_vertex.glsl
	// TBN model shader (conversion in fragment): Assets/shaders/vertex/model_normals_TBN_fragment.glsl; Assets/shaders/fragment/model_normals_TBN_fragment.glsl

// Textured Cube Shaders
	// Standard (diffuse & specular components): Assets/shaders/vertex/cube_textured.glsl; Assets/shaders/fragment/cube_textured.glsl
	// No Specular: : Assets/shaders/vertex/cube_textured_no_specular.glsl; Assets/shaders/fragment/cube_textured_no_specular.glsl

SceneLoader::SceneLoader(ShaderResource& shader_resource, ModelResource& model_resource, 
	                     TextureResource& texture_resource, LightResource& light_resource)
	:m_shader_resource{ shader_resource },
	 m_model_resource{ model_resource },
	 m_texture_resource{ texture_resource },
	 m_light_resource{ light_resource }{
}

void SceneLoader::single_cube(entt::registry& registry) {

	m_shader_resource.load("single_cube", "Assets/shaders/vertex/cube_colored.glsl", "Assets/shaders/fragment/cube_colored.glsl");
	IShaderProgram* shader_program = m_shader_resource.get("single_cube");
	attach_scene_light(*shader_program);
	attach_dirlight(*shader_program);
		
	shader_program->set_uniform("diffuse_material.m_sampler", glm::vec3(0.9f, 0.1f, 0.31f));
	shader_program->set_uniform("specular_material.m_sampler", glm::vec3(0.5f, 0.5f, 0.5f));
	shader_program->set_uniform("specular_material.m_shininess", 32.0f);

	const entt::entity cube_entity = registry.create();
	registry.emplace<ShaderComponent>(cube_entity, shader_program);
	registry.emplace<CubeComponent>(cube_entity, CubeResource::get("cube_normal"));
	registry.emplace<TransformComponent>(cube_entity, glm::vec3{ 0, 0, 0 });

	const entt::entity cube_entity2 = registry.create();
	registry.emplace<ShaderComponent>(cube_entity2, shader_program);
	registry.emplace<CubeComponent>(cube_entity2, CubeResource::get("cube_normal"));
	registry.emplace<TransformComponent>(cube_entity2, glm::vec3{ 6, 0, 0 });
	
}

void SceneLoader::single_cube_textured(entt::registry& registry) {

	m_shader_resource.load("single_cube_textured", "Assets/shaders/vertex/cube_textured_no_specular.glsl", "Assets/shaders/fragment/cube_textured_no_specular.glsl");
	IShaderProgram* shader_program = m_shader_resource.get("single_cube_textured");
	
	m_texture_resource.load("colorful_squares", "Assets/textures/colorful_squares.jpg");
	//m_texture_resource.load("transparent_specular", "Assets/textures/transparent_specular.png");

	attach_scene_light(*shader_program);
	attach_dirlight(*shader_program);
	shader_program->attach_diffuse_texture(*m_texture_resource.get("colorful_squares"));
	//shader_program->attach_specular_texture("transparent_specular", 32.0f);

	const entt::entity textured_cube_entity = registry.create();
	registry.emplace<ShaderComponent>(textured_cube_entity, shader_program);
	registry.emplace<TexturedCubeComponent>(textured_cube_entity, CubeResource::get("cube_normal_textured"));
	registry.emplace<TransformComponent>(textured_cube_entity, glm::vec3{ 5.0f, 0.0f, 0.0f });
	// registry.emplace<RotationComponent>(textured_cube_entity, 0.0f, -0.2f, 0.0f, 0.0f);
}

void SceneLoader::grid(entt::registry& registry){
	m_shader_resource.load("grid_shader", "Assets/shaders/vertex/model.glsl", "Assets/shaders/fragment/model.glsl");
	IShaderProgram* shader_program = m_shader_resource.get("grid_shader");	
	m_model_resource.load("grid", "Assets/models/metal_grid/metal_grid.obj", *shader_program, m_texture_resource, false);
	attach_scene_light(*shader_program);
	attach_dirlight(*shader_program);

	const entt::entity model_entity = registry.create();
	registry.emplace<ModelComponent>(model_entity, m_model_resource.get("grid"));
	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
	registry.emplace<ShaderComponent>(model_entity, shader_program);
}

void SceneLoader::single_model(entt::registry& registry){

	//m_shader_resource.load("model_shader", "Assets/shaders/vertex/model_normals_TBN_fragment.glsl", "Assets/shaders/fragment/model_normals_TBN_fragment.glsl");
	m_shader_resource.load("model_shader", "Assets/shaders/vertex/model.glsl", "Assets/shaders/fragment/model.glsl");
	IShaderProgram* shader_program = m_shader_resource.get("model_shader");
	
	m_model_resource.load("backpack", "Assets/models/backpack/backpack.obj", *shader_program, m_texture_resource, false);
	attach_scene_light(*shader_program);
	attach_dirlight(*shader_program);

	const entt::entity model_entity = registry.create();
	registry.emplace<ModelComponent>(model_entity, m_model_resource.get("backpack"));
	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
	registry.emplace<ShaderComponent>(model_entity, shader_program);
	registry.emplace<RotationComponent>(model_entity, 0.0f, 0.005f, 0.0f, 0.0f);
	// registry.emplace<ScaleComponent>(model_entity, 5.0f);
}

void SceneLoader::cubemap(entt::registry& registry){

	m_shader_resource.load("cubemap", "Assets/shaders/vertex/cubemap.glsl", "Assets/shaders/fragment/cubemap.glsl");
	IShaderProgram* shader_program = m_shader_resource.get("cubemap");

	m_texture_resource.load_cubemap_textures("blue_night", "Assets/cubemaps/space_red");
	shader_program->attach_cubemap_texture(*m_texture_resource.get("blue_night"));
	
	const entt::entity cubemap_entity = registry.create();
	registry.emplace<ShaderComponent>(cubemap_entity, shader_program);
	registry.emplace<CubeMapComponent>(cubemap_entity, CubeResource::get("cubemap"));
	
}

void SceneLoader::voxels(entt::registry& registry){

	m_shader_resource.load("voxel_shader", "Assets/shaders/voxel/vertex/cube_colored.glsl", "Assets/shaders/voxel/fragment/cube_colored.glsl");
	IShaderProgram* shader_program = m_shader_resource.get("voxel_shader");
	shader_program->set_uniform("diffuse_material.m_sampler", glm::vec3(0.2f, 0.7f, 0.31f)); // Temp for setting cube color.  This will normally be a texture.
	//TODO attach texture map here using the shader attach texture function
	attach_scene_light(*shader_program);
	attach_dirlight(*shader_program);
}

void SceneLoader::attach_dirlight(IShaderProgram& shader_program){
	DirectionalLight dirlight{"dirlight"};
	dirlight.m_direction = glm::vec3(0.3f, 0.7f, 0.0f);	
	m_light_resource.load(dirlight);
	shader_program.attach_directional_light(dirlight);

	//DirectionalLight dirlight2{ "dirlight" };
	//dirlight2.m_direction = glm::vec3(0.0f, -1.0f, 0.0f);
	//m_light_resource.load(dirlight2);
	//shader_program.attach_directional_light(dirlight2);
}

void SceneLoader::attach_scene_light(IShaderProgram& shader_program){
	SceneLight scenelight{ "scenelight" };
	scenelight.m_ambient = glm::vec3(0.6f); // 0.6
	scenelight.m_diffuse = glm::vec3(0.5f); // 0.5
	scenelight.m_specular = glm::vec3(1.0f); // 1.0
	m_light_resource.load(scenelight);
	shader_program.attach_scene_light(scenelight);
}

void SceneLoader::attach_point_light(IShaderProgram& shader_program){
	// PointLight pointlight1;
	// pointlight1.m_position = glm::vec3(128.0f, 20.0f, 128.0f);
	// LightResource::load("pointlight1", pointlight1);
	// Dont forget to attach to the shader program

	// PointLight pointlight2;
	// pointlight2.m_position = glm::vec3(0.0f, 2.0f, -5.0f);
	// LightResource::load("pointlight2", pointlight2);
}

void SceneLoader::load_scene(entt::registry& registry){
	// TODO shader loader or some alternative for voxels?
	voxels(registry);
	//grid(registry);
	//single_cube(registry);
	//single_cube_textured(registry);
	single_model(registry);
	cubemap(registry);
}
