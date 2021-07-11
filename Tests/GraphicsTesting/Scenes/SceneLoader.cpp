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

	// Fragment No Specular Material
	// Assets/shaders/fragment/model_no_specular_texture.glsl
	// Assets/shaders/fragment/model_normals_TBN_fragment_no_specular_texture.glsl

// Textured Cube Shaders
	// Standard (diffuse & specular components): Assets/shaders/vertex/cube_textured.glsl; Assets/shaders/fragment/cube_textured.glsl
	// No Specular: : Assets/shaders/vertex/cube_textured_no_specular.glsl; Assets/shaders/fragment/cube_textured_no_specular.glsl

SceneLoader::SceneLoader(ShaderResource& shader_resource, ModelResource& model_resource, 
	                     TextureResource& texture_resource, LightResource& light_resource,
						 CubeResource& cube_resource, IFrameBuffer& framebuffer)
	:m_shader_resource{ shader_resource },
	m_model_resource{ model_resource },
	m_texture_resource{ texture_resource },
	m_light_resource{ light_resource },
	m_cube_resource{ cube_resource },
	m_framebuffer{ framebuffer }{
}

void SceneLoader::load_scene(entt::registry& registry) const{
	// TODO shader loader or some alternative for voxels?
	// voxels(registry);
	
	//grid(registry);
	//single_cube(registry);
	single_cube_textured(registry);
	load_backpack(registry);
	//cubemap(registry);
	//load_framebuffer(registry);
}

void SceneLoader::grid(entt::registry& registry) const{
	m_shader_resource.load("grid_shader", "Assets/shaders/model_shaders/grid/grid_vertex_shader.glsl", "Assets/shaders/model_shaders/grid/grid_fragment_shader.glsl", true);
	IShaderProgram* shader_program = m_shader_resource.get("grid_shader");
	
	m_model_resource.load("grid", "Assets/models/metal_grid/metal_grid.obj", *shader_program, m_texture_resource, false);

	// The grid does not have a specular material.  The scenelight has a
	// specular value that is used in conjuction with the material.  As such.
	// we need to only set the uniforms of the ambient and diffuse portions
	// of the scenelight

	const SceneLight* scene_light = m_light_resource.get_scenelight("standard_scenelight1");
	shader_program->set_uniform("scenelight.ambient", scene_light->m_ambient);
	shader_program->set_uniform("scenelight.diffuse", scene_light->m_diffuse);

	shader_program->attach_directional_light(*m_light_resource.get_dirlight("standard_dirlight1"));
		
	const entt::entity model_entity = registry.create();
	registry.emplace<ModelComponent>(model_entity, m_model_resource.get("grid"));
	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, -0.5f, 0.0f });
	registry.emplace<ShaderComponent>(model_entity, shader_program);
}

void SceneLoader::single_cube(entt::registry& registry) const {

	m_shader_resource.load("single_cube", "Assets/shaders/model_shaders/colored_cube/colored_cube_vertex.glsl", "Assets/shaders/model_shaders/colored_cube/colored_cube_fragment.glsl", true);
	
	IShaderProgram* shader_program = m_shader_resource.get("single_cube");

	shader_program->attach_scene_light(*m_light_resource.get_scenelight("standard_scenelight1"));
	shader_program->attach_directional_light(*m_light_resource.get_dirlight("standard_dirlight1"));
		
	shader_program->set_uniform("diffuse_color", glm::vec3(0.9f, 0.1f, 0.31f));
	shader_program->set_uniform("specular_color", glm::vec3(0.5f, 0.5f, 0.5f));
	shader_program->set_uniform("specular_shininess", 32.0f);

	const entt::entity cube_entity = registry.create();
	registry.emplace<ShaderComponent>(cube_entity, shader_program);
	registry.emplace<CubeComponent>(cube_entity, m_cube_resource.get("cube_normal"));
	registry.emplace<TransformComponent>(cube_entity, glm::vec3{ 0, 0, 0 });
	
}

void SceneLoader::single_cube_textured(entt::registry& registry) const {

	m_shader_resource.load("single_cube_textured", "Assets/shaders/model_shaders/textured_cube/textured_cube_vertex.glsl", "Assets/shaders/model_shaders/textured_cube/textured_cube_fragment.glsl", true);
	m_texture_resource.load("brown_container", "Assets/textures/brown_container.png");
	m_texture_resource.load("brown_container_specular", "Assets/textures/container_specular_map.png");
	
	IShaderProgram* shader_program = m_shader_resource.get("single_cube_textured");
	
	shader_program->attach_diffuse_texture(*m_texture_resource.get("brown_container"));
	shader_program->attach_specular_texture(*m_texture_resource.get("brown_container_specular"), 32.0f);

	
	shader_program->attach_scene_light(*m_light_resource.get_scenelight("standard_scenelight1"));
	// shader_program->attach_directional_light(*m_light_resource.get_dirlight("standard_dirlight1"));

	const PointLight pointlight{ "testing_pointlight", glm::vec3{2.0f, 0.0f, 1.5f }, 1.0f, 0.7f, 1.8f };
	m_light_resource.load(pointlight);
	shader_program->attach_point_light(*m_light_resource.get_pointlight("testing_pointlight"));

	const entt::entity textured_cube_entity = registry.create();
	registry.emplace<ShaderComponent>(textured_cube_entity, shader_program);
	registry.emplace<TexturedCubeComponent>(textured_cube_entity, m_cube_resource.get("cube_normal_textured"));
	registry.emplace<TransformComponent>(textured_cube_entity, glm::vec3{ 4.0f, 0.0f, 0.0f });
	// registry.emplace<RotationComponent>(textured_cube_entity, 0.0f, -0.002f, 0.0f, 0.0f);
}

void SceneLoader::load_backpack(entt::registry& registry) const{

	const std::string id = "backpack";
	m_shader_resource.load(id, "Assets/shaders/model_shaders/backpack/backpack_vertex.glsl", "Assets/shaders/model_shaders/backpack/backpack_fragment.glsl", true);
	IShaderProgram* shader_program = m_shader_resource.get(id);
	
	m_model_resource.load(id, "Assets/models/backpack/backpack.obj", *shader_program, m_texture_resource, false);
	shader_program->attach_scene_light(*m_light_resource.get_scenelight("standard_scenelight1"));
	shader_program->attach_directional_light(*m_light_resource.get_dirlight("standard_dirlight1"));

	// PointLight pointlight{ "testing_pointlight2", glm::vec3{1000000.0f, 0.0f, 0.0f }, 1.0f, 0.09f, 0.032f };
	// m_light_resource.load(pointlight);
	// shader_program->attach_point_light(pointlight);
	
	const entt::entity model_entity = registry.create();
	registry.emplace<ModelComponent>(model_entity, m_model_resource.get(id));
	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
	registry.emplace<ShaderComponent>(model_entity, shader_program);
	// registry.emplace<RotationComponent>(model_entity, 0.0f, 0.009f, 0.0f, 0.0f);
	// registry.emplace<ScaleComponent>(model_entity, 5.0f);
}

















//

//
//void SceneLoader::models(entt::registry& registry){
//
//	// load_test_any_model(registry);
//	// load_cerberus(registry);
//	// load_mech(registry);
//	// load_vivi()
//	// load_spartan(registry);
//	load_backpack(registry);
//	// load_troll(registry);
//	// load_podracer(registry);
//	
//}
//
//void SceneLoader::load_backpack(entt::registry& registry){
//
//	const std::string id = "backpack";
//	m_shader_resource.load(id, "Assets/shaders/vertex/model_normals_TBN_fragment.glsl", "Assets/shaders/fragment/model_normals_TBN_fragment.glsl", true);
//	IShaderProgram* shader_program = m_shader_resource.get(id);
//	m_model_resource.load(id, "Assets/models/backpack/backpack.obj", *shader_program, m_texture_resource, false);
//	//attach_scene_light(*shader_program);
//	//attach_dirlight(*shader_program);
//
//	const entt::entity model_entity = registry.create();
//	registry.emplace<ModelComponent>(model_entity, m_model_resource.get(id));
//	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
//	registry.emplace<ShaderComponent>(model_entity, shader_program);
//	registry.emplace<RotationComponent>(model_entity, 0.0f, 0.009f, 0.0f, 0.0f);
//	// registry.emplace<ScaleComponent>(model_entity, 5.0f);
//}
//
//void SceneLoader::load_troll(entt::registry& registry){
//
//	const std::string id = "troll";
//	//m_shader_resource.load("troll_shader", "Assets/shaders/vertex/model.glsl", "Assets/shaders/fragment/model_no_specular_texture.glsl"); // No normal map used
//	m_shader_resource.load(id, "Assets/shaders/vertex/model_normals_TBN_fragment.glsl", "Assets/shaders/fragment/model_normals_TBN_fragment_no_specular_texture.glsl", true);
//	IShaderProgram* shader_program = m_shader_resource.get(id);
//	m_model_resource.load(id, "Assets/models/troll/scene.gltf", *shader_program, m_texture_resource, true);
//	//attach_scene_light(*shader_program);
//	//attach_dirlight(*shader_program);
//	
//	const entt::entity model_entity = registry.create();
//	registry.emplace<ModelComponent>(model_entity, m_model_resource.get(id));
//	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 50.0f, 0.0f, 0.0f });
//	registry.emplace<ShaderComponent>(model_entity, shader_program);
//	
//}
//
//void SceneLoader::load_podracer(entt::registry& registry){
//
//	const std::string id = "podracer";
//	m_shader_resource.load(id, "Assets/shaders/vertex/model.glsl", "Assets/shaders/fragment/model_no_specular_texture.glsl", true);
//	IShaderProgram* shader_program = m_shader_resource.get(id);
//	m_model_resource.load(id, "Assets/models/podracer/scene.gltf", *shader_program, m_texture_resource, true);
//	//attach_scene_light(*shader_program);
//	//attach_dirlight(*shader_program);
//
//	const entt::entity model_entity = registry.create();
//	registry.emplace<ModelComponent>(model_entity, m_model_resource.get(id));
//	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
//	registry.emplace<ShaderComponent>(model_entity, shader_program);
//	// registry.emplace<RotationComponent>(model_entity, 0.0f, 0.009f, 0.0f, 0.0f);
//}
//
//void SceneLoader::load_spartan(entt::registry& registry){
//	const std::string id = "spartan";
//	m_shader_resource.load(id, "Assets/shaders/vertex/model_normals_TBN_fragment.glsl", "Assets/shaders/fragment/model_normals_TBN_fragment_no_specular_texture.glsl", true);
//	IShaderProgram* shader_program = m_shader_resource.get(id);
//	m_model_resource.load(id, "Assets/models/spartan/scene.gltf", *shader_program, m_texture_resource, true);
//	//attach_scene_light(*shader_program);
//	//attach_dirlight(*shader_program);
//
//	const entt::entity model_entity = registry.create();
//	registry.emplace<ModelComponent>(model_entity, m_model_resource.get(id));
//	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
//	registry.emplace<ShaderComponent>(model_entity, shader_program);
//}
//
//void SceneLoader::load_vivi(entt::registry& registry){
//	const std::string id = "vivi";
//	m_shader_resource.load(id, "Assets/shaders/vertex/model_normals_TBN_fragment.glsl", "Assets/shaders/fragment/model_normals_TBN_fragment_no_specular_texture.glsl", true);
//	IShaderProgram* shader_program = m_shader_resource.get(id);
//	m_model_resource.load(id, "Assets/models/vivi/scene.gltf", *shader_program, m_texture_resource, true);
//	//attach_scene_light(*shader_program);
//	//attach_dirlight(*shader_program);
//
//	const entt::entity model_entity = registry.create();
//	registry.emplace<ModelComponent>(model_entity, m_model_resource.get(id));
//	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
//	registry.emplace<ShaderComponent>(model_entity, shader_program);
//}
//
//void SceneLoader::load_mech(entt::registry& registry){
//	const std::string id = "mech_drone";
//	m_shader_resource.load(id, "Assets/shaders/vertex/model_normals_TBN_fragment.glsl", "Assets/shaders/fragment/model_normals_TBN_fragment_no_specular_texture.glsl", true);
//	IShaderProgram* shader_program = m_shader_resource.get(id);
//	m_model_resource.load(id, "Assets/models/mech_drone/scene.gltf", *shader_program, m_texture_resource, true);
//	//attach_scene_light(*shader_program);
//	//attach_dirlight(*shader_program);
//
//	const entt::entity model_entity = registry.create();
//	registry.emplace<ModelComponent>(model_entity, m_model_resource.get(id));
//	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
//	registry.emplace<ShaderComponent>(model_entity, shader_program);
//}
//
//void SceneLoader::load_cerberus(entt::registry& registry){
//	const std::string id = "cerberus";
//	m_shader_resource.load(id, "Assets/shaders/vertex/model_normals_TBN_fragment.glsl", "Assets/shaders/fragment/model_normals_TBN_fragment_no_specular_texture.glsl", true);
//	IShaderProgram* shader_program = m_shader_resource.get(id);
//	m_model_resource.load(id, "Assets/models/cerberus/scene.gltf", *shader_program, m_texture_resource, true);
//	//attach_scene_light(*shader_program);
//	//attach_dirlight(*shader_program);
//
//	const entt::entity model_entity = registry.create();
//	registry.emplace<ModelComponent>(model_entity, m_model_resource.get(id));
//	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
//	registry.emplace<ShaderComponent>(model_entity, shader_program);
//}
//
//void SceneLoader::load_test_any_model(entt::registry& registry){
//	const std::string id = "planet";
//	m_shader_resource.load(id, "Assets/shaders/vertex/model_normals_TBN_fragment.glsl", "Assets/shaders/fragment/model_normals_TBN_fragment_no_specular_texture.glsl", true);
//	IShaderProgram* shader_program = m_shader_resource.get(id);
//	m_model_resource.load(id, "Assets/models/planet/planet.obj", *shader_program, m_texture_resource, true);
//	//attach_scene_light(*shader_program);
//	//attach_dirlight(*shader_program);
//
//	const entt::entity model_entity = registry.create();
//	registry.emplace<ModelComponent>(model_entity, m_model_resource.get(id));
//	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, 0.0f, 0.0f });
//	registry.emplace<ShaderComponent>(model_entity, shader_program);
//}
//
//
//void SceneLoader::cubemap(entt::registry& registry){
//
//	m_shader_resource.load("cubemap", "Assets/shaders/vertex/cubemap.glsl", "Assets/shaders/fragment/cubemap.glsl", false);
//	IShaderProgram* shader_program = m_shader_resource.get("cubemap");
//
//	m_texture_resource.load_cubemap_textures("blue_night", "Assets/cubemaps/space_red");
//	shader_program->attach_cubemap_texture(*m_texture_resource.get("blue_night"));
//	
//	const entt::entity cubemap_entity = registry.create();
//	registry.emplace<ShaderComponent>(cubemap_entity, shader_program);
//	registry.emplace<CubeMapComponent>(cubemap_entity, m_cube_resource.get("cubemap"));
//	
//}
//
//void SceneLoader::voxels(entt::registry& registry){
//
//	m_shader_resource.load("voxel_shader", "Assets/shaders/voxel/vertex/cube_colored.glsl", "Assets/shaders/voxel/fragment/cube_colored.glsl", true);
//	IShaderProgram* shader_program = m_shader_resource.get("voxel_shader");
//	shader_program->set_uniform("diffuse_material.m_sampler", glm::vec3(0.2f, 0.7f, 0.31f)); // Temp for setting cube color.  This will normally be a texture.
//	//TODO attach texture map here using the shader attach texture function
//	//attach_scene_light(*shader_program);
//	//attach_dirlight(*shader_program);
//}
//
//void SceneLoader::load_framebuffer(entt::registry& registry){
//	m_shader_resource.load("framebuffer_shader", "Assets/shaders/framebuffer/vertex/framebuffer.glsl", "Assets/shaders/framebuffer/fragment/framebuffer_edge.glsl", false);
//	IShaderProgram* shader_program = m_shader_resource.get("framebuffer_shader");
//	const entt::entity model_entity = registry.create();
//	registry.emplace<ShaderComponent>(model_entity, shader_program);
//	registry.emplace<FrameBufferComponent>(model_entity, &m_framebuffer);
//
//
//}

//void SceneLoader::attach_dirlight(IShaderProgram& shader_program){
//	DirectionalLight dirlight{"dirlight"};
//	dirlight.m_direction = glm::vec3(1.0f, 1.0f, 0.0f);	
//	m_light_resource.load(dirlight);
//	shader_program.attach_directional_light(dirlight);
//
//	//DirectionalLight dirlight2{ "dirlight" };
//	//dirlight2.m_direction = glm::vec3(0.0f, -1.0f, 0.0f);
//	//m_light_resource.load(dirlight2);
//	//shader_program.attach_directional_light(dirlight2);
//}

//void SceneLoader::attach_scene_light(IShaderProgram& shader_program){
//	SceneLight scenelight{ "scenelight" };
//	scenelight.m_ambient = glm::vec3(0.6f); // 0.6
//	scenelight.m_diffuse = glm::vec3(0.5f); // 0.5
//	scenelight.m_specular = glm::vec3(1.0f); // 1.0
//	m_light_resource.load(scenelight);
//	shader_program.attach_scene_light(scenelight);
//}
//
//void SceneLoader::attach_point_light(IShaderProgram& shader_program){
//	 PointLight pointlight1{"pointlight_one"};
//	 pointlight1.m_position = glm::vec3(128.0f, 20.0f, 128.0f);
//	 m_light_resource.load(pointlight1);
//	 shader_program.attach_point_light(pointlight1);
//
//	// PointLight pointlight2;
//	// pointlight2.m_position = glm::vec3(0.0f, 2.0f, -5.0f);
//	// LightResource::load("pointlight2", pointlight2);
//}


