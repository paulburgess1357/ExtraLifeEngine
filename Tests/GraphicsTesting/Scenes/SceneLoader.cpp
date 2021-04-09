#include "SceneLoader.h"
#include "../../ECS/Components/IncludeComponents.h"
#include "../../ResourceManagement/IncludeResources.h"
#include "../../../Utility/FatalError.h"

// Shaders
// Model Shaders
	// Standard model shader: Assets/shaders/vertex/model.glsl; Assets/shaders/fragment/model.glsl
	// Normals model shader: Assets/shaders/vertex/model_normals.glsl; Assets/shaders/fragment/model_normals.glsl
	// TBN model shader: Assets/shaders/vertex/model_normals_TBN_fragment.glsl; Assets/shaders/fragment/model_normals_TBN_fragment.glsl
// Textured Cube Shaders
	// Standard (diffuse & specular components): Assets/shaders/vertex/cube_textured.glsl; Assets/shaders/fragment/cube_textured.glsl
	// No Specular: : Assets/shaders/vertex/cube_textured_no_specular.glsl; Assets/shaders/fragment/cube_textured_no_specular.glsl


void SceneLoader::single_cube(entt::registry& registry) {

	std::shared_ptr<IShaderProgram> shader_program = ShaderResource::load("single_cube", "Assets/shaders/vertex/cube_colored.glsl", "Assets/shaders/fragment/cube_colored.glsl");
	attach_basic_lighting(shader_program);
		
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

	std::shared_ptr<IShaderProgram> shader_program = ShaderResource::load("single_cube_textured", "Assets/shaders/vertex/cube_textured_no_specular.glsl", "Assets/shaders/fragment/cube_textured_no_specular.glsl");
	
	TextureResource::load("colorful_squares", "Assets/textures/colorful_squares.jpg");
	//TextureResource::load("transparent_specular", "Assets/textures/transparent_specular.png");

	attach_basic_lighting(shader_program);
	shader_program->attach_diffuse_texture("colorful_squares");
	//shader_program->attach_specular_texture("transparent_specular", 32.0f);

	const entt::entity textured_cube_entity = registry.create();
	registry.emplace<ShaderComponent>(textured_cube_entity, shader_program);
	registry.emplace<TexturedCubeComponent>(textured_cube_entity, CubeResource::get("cube_normal_textured"));
	registry.emplace<TransformComponent>(textured_cube_entity, glm::vec3{ 5.0f, 0.0f, 0.0f });
	registry.emplace<RotationComponent>(textured_cube_entity, 0.0f, -0.2f, 0.0f, 0.0f);
}

void SceneLoader::grid(entt::registry& registry){
	std::shared_ptr<IShaderProgram> shader_program = ShaderResource::load("grid_shader", "Assets/shaders/vertex/model.glsl", "Assets/shaders/fragment/model.glsl");
	ModelResource::load("grid", "Assets/models/metal_grid/metal_grid.obj", "grid_shader", false);
	attach_basic_lighting(shader_program);

	const entt::entity model_entity = registry.create();
	registry.emplace<ModelComponent>(model_entity, ModelResource::get("grid"));
	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
	registry.emplace<ShaderComponent>(model_entity, shader_program);
}

void SceneLoader::single_model(entt::registry& registry){

	std::shared_ptr<IShaderProgram> shader_program = ShaderResource::load("model_shader", "Assets/shaders/vertex/model_normals_TBN_fragment.glsl", "Assets/shaders/fragment/model_normals_TBN_fragment.glsl");
	
	ModelResource::load("backpack", "Assets/models/backpack/backpack.obj", "model_shader", false);
	
	attach_basic_lighting(shader_program);

	const entt::entity model_entity = registry.create();
	registry.emplace<ModelComponent>(model_entity, ModelResource::get("backpack"));
	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
	registry.emplace<ShaderComponent>(model_entity, shader_program);
	registry.emplace<RotationComponent>(model_entity, 0.0f, 0.02f, 0.0f, 0.0f);
}

void SceneLoader::cubemap(entt::registry& registry){

	std::shared_ptr<IShaderProgram> shader_program = ShaderResource::load("cubemap", "Assets/shaders/vertex/cubemap.glsl", "Assets/shaders/fragment/cubemap.glsl", false);	
	TextureResource::load_cubemap_textures("space_red", "Assets/cubemaps/milkyway");
	shader_program->attach_cubemap_texture("space_red");
	
	const entt::entity cubemap_entity = registry.create();
	registry.emplace<ShaderComponent>(cubemap_entity, shader_program);
	registry.emplace<CubeMapComponent>(cubemap_entity, CubeResource::get("cubemap"));
	
}

void SceneLoader::voxels(entt::registry& registry){

	// Load starting chunks
	VoxelResource::load(32, 1, 32);

	// Load chunks into entities.  Each entity is a single chunk:
	load_chunks_into_entities(registry);
	
}

void SceneLoader::load_chunks_into_entities(entt::registry& registry){

	// Voxel Shader:
	std::shared_ptr<IShaderProgram> shader_program = ShaderResource::load("voxel_shader", "Assets/shaders/voxel/vertex/cube_colored.glsl", "Assets/shaders/voxel/fragment/cube_colored.glsl");
	shader_program->set_uniform("diffuse_material.m_sampler", glm::vec3(0.2f, 0.7f, 0.31f)); // Temp for setting cube color.  This will normally be a texture.
	attach_basic_lighting(shader_program);
	//TODO attach texture map here using the shader attach texture function

	for(auto& chunk : VoxelResource::get_chunkmap()){

		const entt::entity chunk_entity = registry.create();

		// Load Chunk Components
		registry.emplace<ChunkComponent>(chunk_entity, chunk.second);
						
		// Load chunk model matrix
		registry.emplace<TransformComponent>(chunk_entity, chunk.second->get_starting_world_position().get_vec3());
		
		// Load shader program
		registry.emplace<VoxelShaderComponent>(chunk_entity, shader_program);
	}
}


void SceneLoader::attach_basic_lighting(std::shared_ptr<IShaderProgram>& shader_program){
	DirectionalLight dirlight;
	dirlight.m_direction = glm::vec3(1.0f, 0.5f, 0.0f);
	LightResource::load("dirlight", dirlight);

	PointLight pointlight1;
	pointlight1.m_position = glm::vec3(128.0f, 20.0f, 128.0f);
	LightResource::load("pointlight1", pointlight1);

	// PointLight pointlight2;
	// pointlight2.m_position = glm::vec3(0.0f, 2.0f, -5.0f);
	// LightResource::load("pointlight2", pointlight2);

	//shader_program->attach_directional_light("dirlight");
	shader_program->attach_point_light("pointlight1");
	// shader_program->attach_point_light("pointlight2");
}

