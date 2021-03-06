#include "SceneLoader.h"

#include "../../ECS/Components/IncludeComponents.h"
#include "../../ResourceManagement/IncludeResources.h"

SceneLoader::SceneLoader(ShaderResource& shader_resource, ModelResource& model_resource, 
	                     TextureResource& texture_resource, LightResource& light_resource,
						 CubeResource& cube_resource)
	:m_shader_resource{ shader_resource },
	m_model_resource{ model_resource },
	m_texture_resource{ texture_resource },
	m_light_resource{ light_resource },
	m_cube_resource{ cube_resource }{
}

void SceneLoader::load_scene(entt::registry& registry) {

	// Shader Book
	// single_cube_diffuse_lighting(registry);
	// single_cube_phong_lighting(registry);
	// single_cube_discard_effect(registry);
	single_cube_multiple_positional_lights(registry);

	
	// voxels(registry, 7, 3, 7);	
	// grid(registry);
	// single_cube(registry);
	// single_cube_textured(registry);
	// load_backpack(registry);
	// load_spartan(registry);
	// cubemap(registry);
}

void SceneLoader::single_cube_diffuse_lighting(entt::registry& registry) const{
	m_shader_resource.load("single_cube", "Assets/shaders/model_shaders_view_space/colored_cube/diffuse_vertex_shading.glsl", "Assets/shaders/model_shaders_view_space/colored_cube/diffuse_fragment_shading.glsl", true);
	IShaderProgram* shader_program = m_shader_resource.get("single_cube");

	shader_program->set_uniform("light_position_in_world", glm::vec3(100.0f, 20.0f, 0.0f));
	shader_program->set_uniform("light_intensity", glm::vec3(1.0f));
	shader_program->set_uniform("diffuse_color", glm::vec3(0.2f, 0.4f, 0.2f));

	const entt::entity cube_entity = registry.create();
	registry.emplace<ShaderComponent>(cube_entity, shader_program);
	registry.emplace<CubeComponent>(cube_entity, m_cube_resource.get("cube_normal"));
	registry.emplace<TransformComponent>(cube_entity, glm::vec3{ 0, 0, 0 });
}


void SceneLoader::single_cube_phong_lighting(entt::registry& registry) const{	
	
	// m_shader_resource.load("single_cube", "Assets/shaders/model_shaders_view_space/colored_cube/2_phong_vertex_shading.glsl", "Assets/shaders/model_shaders_view_space/colored_cube/2_phong_fragment_shading.glsl", true);
	// m_shader_resource.load("single_cube", "Assets/shaders/model_shaders_view_space/colored_cube/3_phong_equation_vertex_shading.glsl", "Assets/shaders/model_shaders_view_space/colored_cube/3_phong_equation_fragment_shading.glsl", true);
	m_shader_resource.load("single_cube", "Assets/shaders/model_shaders_view_space/colored_cube/4_phong_2sided_vertex_shading.glsl", "Assets/shaders/model_shaders_view_space/colored_cube/4_phong_2sided_fragment_shading.glsl", true);
	IShaderProgram* shader_program = m_shader_resource.get("single_cube");

	shader_program->set_uniform("light_info.light_position_in_world", glm::vec3(0.0f, 20.0f, 0.0f));
	
	shader_program->set_uniform("light_info.ambient_light_intensity", glm::vec3(0.4f));
	shader_program->set_uniform("light_info.diffuse_light_intensity", glm::vec3(1.0f));
	shader_program->set_uniform("light_info.specular_light_intensity", glm::vec3(1.0f));

	shader_program->set_uniform("material_info.ambient_reflectivity", glm::vec3(0.9f, 0.5f, 0.3f));
	shader_program->set_uniform("material_info.diffuse_reflectivity", glm::vec3(0.9f, 0.5f, 0.3f));
	
	shader_program->set_uniform("material_info.specular_reflectivity", glm::vec3(0.8f, 0.8f, 0.8f));
	shader_program->set_uniform("material_info.shininess", 100.0f);

	const entt::entity cube_entity = registry.create();
	registry.emplace<ShaderComponent>(cube_entity, shader_program);
	registry.emplace<CubeComponent>(cube_entity, m_cube_resource.get("cube_normal"));
	registry.emplace<TransformComponent>(cube_entity, glm::vec3{ 0, 0, 0 });
}

void SceneLoader::single_cube_discard_effect(entt::registry& registry) const{

	m_shader_resource.load("single_cube", "Assets/shaders/model_shaders_view_space/colored_cube/5_phong_discard_vertex_shading.glsl", "Assets/shaders/model_shaders_view_space/colored_cube/5_phong_discard_fragment_shading.glsl", true);
	IShaderProgram* shader_program = m_shader_resource.get("single_cube");

	shader_program->set_uniform("light_info.light_position_in_world", glm::vec3(0.0f, 20.0f, 0.0f));

	shader_program->set_uniform("light_info.ambient_light_intensity", glm::vec3(0.4f));
	shader_program->set_uniform("light_info.diffuse_light_intensity", glm::vec3(1.0f));
	shader_program->set_uniform("light_info.specular_light_intensity", glm::vec3(1.0f));

	shader_program->set_uniform("material_info.ambient_reflectivity", glm::vec3(0.9f, 0.5f, 0.3f));
	shader_program->set_uniform("material_info.diffuse_reflectivity", glm::vec3(0.9f, 0.5f, 0.3f));

	shader_program->set_uniform("material_info.specular_reflectivity", glm::vec3(0.8f, 0.8f, 0.8f));
	shader_program->set_uniform("material_info.shininess", 100.0f);

	const entt::entity cube_entity = registry.create();
	registry.emplace<ShaderComponent>(cube_entity, shader_program);
	registry.emplace<CubeComponent>(cube_entity, m_cube_resource.get("cube_normal_textured"));
	registry.emplace<TransformComponent>(cube_entity, glm::vec3{ 0, 0, 0 });
}

void SceneLoader::single_cube_multiple_positional_lights(entt::registry& registry) const{

	// Note: No attenuation or anything is taken into account with this example.
	
	m_shader_resource.load("single_cube", "Assets/shaders/model_shaders_view_space/colored_cube/6_phong_positional_lights_vertex_shading.glsl", "Assets/shaders/model_shaders_view_space/colored_cube/6_phong_positional_lights_fragment_shading.glsl", true);
	IShaderProgram* shader_program = m_shader_resource.get("single_cube");

	// Positional Light #1
	shader_program->set_uniform("light_info[0].light_position_in_world", glm::vec3(0.0f, 20.0f, 0.0f));
	shader_program->set_uniform("light_info[0].ambient_light_intensity", glm::vec3(0.4f));
	shader_program->set_uniform("light_info[0].diffuse_specular_light_intensity", glm::vec3(1.0f));

	// Positional Light #2
	shader_program->set_uniform("light_info[1].light_position_in_world", glm::vec3(0.0f, -20.0f, 0.0f));
	shader_program->set_uniform("light_info[1].ambient_light_intensity", glm::vec3(0.4f));
	shader_program->set_uniform("light_info[1].diffuse_specular_light_intensity", glm::vec3(1.0f));

	// Material
	shader_program->set_uniform("material_info.ambient_reflectivity", glm::vec3(0.9f, 0.5f, 0.3f));
	shader_program->set_uniform("material_info.diffuse_reflectivity", glm::vec3(0.9f, 0.5f, 0.3f));

	shader_program->set_uniform("material_info.specular_reflectivity", glm::vec3(0.8f, 0.8f, 0.8f));
	shader_program->set_uniform("material_info.shininess", 100.0f);

	const entt::entity cube_entity = registry.create();
	registry.emplace<ShaderComponent>(cube_entity, shader_program);
	registry.emplace<CubeComponent>(cube_entity, m_cube_resource.get("cube_normal"));
	registry.emplace<TransformComponent>(cube_entity, glm::vec3{ 0, 0, 0 });
	
}





void SceneLoader::grid(entt::registry& registry) const{
	m_shader_resource.load("grid_shader", "Assets/shaders/model_shaders_view_space/grid/grid_vertex_shader.glsl", "Assets/shaders/model_shaders_view_space/grid/grid_fragment_shader.glsl", true);
	IShaderProgram* shader_program = m_shader_resource.get("grid_shader");
	m_model_resource.load("grid", "Assets/models/metal_grid/metal_grid.obj", *shader_program, m_texture_resource, false);
	
	const SceneLight* scene_light = m_light_resource.get_scenelight("standard_scenelight");
	shader_program->set_uniform("scenelight.ambient", scene_light->m_ambient);
	shader_program->set_uniform("scenelight.diffuse", scene_light->m_diffuse);
	shader_program->attach_directional_light(*m_light_resource.get_dirlight("standard_dirlight"));
		
	const entt::entity model_entity = registry.create();
	registry.emplace<ModelComponent>(model_entity, m_model_resource.get("grid"));
	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 0.0f, -0.5f, 0.0f });
	registry.emplace<ShaderComponent>(model_entity, shader_program);
}

void SceneLoader::single_cube(entt::registry& registry) const {

	m_shader_resource.load("single_cube", "Assets/shaders/model_shaders_view_space/colored_cube/colored_cube_vertex.glsl", "Assets/shaders/model_shaders_view_space/colored_cube/colored_cube_fragment.glsl", true);
	IShaderProgram* shader_program = m_shader_resource.get("single_cube");

	shader_program->attach_scene_light(*m_light_resource.get_scenelight("standard_scenelight"));
	shader_program->attach_directional_light(*m_light_resource.get_dirlight("standard_dirlight"));
		
	shader_program->set_uniform("diffuse_color", glm::vec3(0.9f, 0.1f, 0.31f));
	shader_program->set_uniform("specular_color", glm::vec3(0.5f, 0.5f, 0.5f));
	shader_program->set_uniform("specular_shininess", 32.0f);

	const entt::entity cube_entity = registry.create();
	registry.emplace<ShaderComponent>(cube_entity, shader_program);
	registry.emplace<CubeComponent>(cube_entity, m_cube_resource.get("cube_normal"));
	registry.emplace<TransformComponent>(cube_entity, glm::vec3{ 0, 0, 0 });
	
}

void SceneLoader::single_cube_textured(entt::registry& registry) const {

	m_shader_resource.load("single_cube_textured", "Assets/shaders/model_shaders_view_space/textured_cube/textured_cube_vertex.glsl", "Assets/shaders/model_shaders_view_space/textured_cube/textured_cube_fragment.glsl", true);
	m_texture_resource.load("brown_container", "Assets/textures/brown_container.png", true);
	m_texture_resource.load("brown_container_specular", "Assets/textures/container_specular_map.png", false);
	
	IShaderProgram* shader_program = m_shader_resource.get("single_cube_textured");
	
	shader_program->attach_diffuse_texture(*m_texture_resource.get("brown_container"));
	shader_program->attach_specular_texture(*m_texture_resource.get("brown_container_specular"), 32.0f);
	
	shader_program->attach_scene_light(*m_light_resource.get_scenelight("standard_scenelight"));
	shader_program->attach_directional_light(*m_light_resource.get_dirlight("standard_dirlight"));
	shader_program->attach_point_light(*m_light_resource.get_pointlight("standard_pointlight"));

	const entt::entity textured_cube_entity = registry.create();
	registry.emplace<ShaderComponent>(textured_cube_entity, shader_program);
	registry.emplace<TexturedCubeComponent>(textured_cube_entity, m_cube_resource.get("cube_normal_textured"));
	registry.emplace<TransformComponent>(textured_cube_entity, glm::vec3{ 4.0f, 0.0f, 0.0f });
	// registry.emplace<RotationComponent>(textured_cube_entity, 0.0f, -0.002f, 0.0f, 0.0f);
}

void SceneLoader::load_backpack(entt::registry& registry) const{

	const std::string id = "backpack";
	m_shader_resource.load(id, "Assets/shaders/model_shaders_view_space/backpack/backpack_vertex.glsl", "Assets/shaders/model_shaders_view_space/backpack/backpack_fragment.glsl", true);
	IShaderProgram* shader_program = m_shader_resource.get(id);
	
	m_model_resource.load(id, "Assets/models/backpack/backpack.obj", *shader_program, m_texture_resource, false);
	shader_program->attach_scene_light(*m_light_resource.get_scenelight("standard_scenelight"));
	shader_program->attach_directional_light(*m_light_resource.get_dirlight("standard_dirlight"));
	//shader_program->attach_point_light(*m_light_resource.get_pointlight("standard_pointlight"));
	
	const entt::entity model_entity = registry.create();
	registry.emplace<ModelComponent>(model_entity, m_model_resource.get(id));
	registry.emplace<TransformComponent>(model_entity, glm::vec3{ 4.0f, 0.0f, 0.0f });
	registry.emplace<ShaderComponent>(model_entity, shader_program);
	registry.emplace<RotationComponent>(model_entity, 0.0f, 0.009f, 0.0f, 0.0f);
	// registry.emplace<ScaleComponent>(model_entity, 5.0f);
}

void SceneLoader::load_spartan(entt::registry& registry) const{

	//TODO add warning for not being able to load a texture (e.g. metallic roughness)
	
	const std::string id = "spartan";
	m_shader_resource.load(id, "Assets/shaders/model_shaders_view_space/spartan/spartan_vertex_testing.glsl", "Assets/shaders/model_shaders_view_space/spartan/spartan_fragment_testing.glsl", true);
	IShaderProgram* shader_program = m_shader_resource.get(id);

	m_model_resource.load(id, "Assets/models/spartan/scene.gltf", *shader_program, m_texture_resource, true);

	// Note: No specular material in spartan, so we must manually load the scene light (it has a specular property)
	// Note2: I'm also making the impact of light higher by adjusting the scenelight diffuse property

	shader_program->attach_directional_light(*m_light_resource.get_dirlight("standard_dirlight"));
	const SceneLight custom_scenelight{ "spartan_scenelight" , glm::vec3{0.01f}, glm::vec3{1.9f}, glm::vec3{0.01f} };
	shader_program->set_uniform("scenelight.ambient", custom_scenelight.m_ambient);
	shader_program->set_uniform("scenelight.diffuse", custom_scenelight.m_diffuse);
	
	//const PointLight custom_pointlight{"spartan_pointlight", glm::vec3{-132.0f, 117.0f, 132.0f}, 1.0f, 0.0014f, 0.000007f };
	//shader_program->attach_point_light(custom_pointlight);

	const entt::entity model_entity = registry.create();
	registry.emplace<ModelComponent>(model_entity, m_model_resource.get(id));
	registry.emplace<TransformComponent>(model_entity, glm::vec3{ -4.0f, 0.0f, 0.0f });
	registry.emplace<ShaderComponent>(model_entity, shader_program);
	//registry.emplace<RotationComponent>(model_entity, 0.0f, 0.003f, 0.0f, 0.0f);	
}

void SceneLoader::cubemap(entt::registry& registry) const{

	const std::string id = "space_red";
	m_shader_resource.load(id, "Assets/shaders/cubemap_shaders/cubemap_vertex.glsl", "Assets/shaders/cubemap_shaders/cubemap_fragment.glsl", true);
	m_texture_resource.load_cubemap_textures(id, "Assets/cubemaps/space_red", true);
	
	IShaderProgram* shader_program = m_shader_resource.get(id);
	shader_program->attach_cubemap_texture(*m_texture_resource.get(id));
	
	const entt::entity cubemap_entity = registry.create();
	registry.emplace<ShaderComponent>(cubemap_entity, shader_program);
	registry.emplace<CubeMapComponent>(cubemap_entity, m_cube_resource.get("cubemap"));
	
}

void SceneLoader::voxels(entt::registry& registry, const int x_range, const int y_range, const int z_range) {

	const std::string id = "voxel_shader";
	m_shader_resource.load(id, "Assets/shaders/voxel_shaders/voxel_vertex.glsl", "Assets/shaders/voxel_shaders/voxel_fragment.glsl", true);
	IShaderProgram* shader_program = m_shader_resource.get(id);
	// Voxel color is determined by its type (temp for testing)
	// This is set in the fragment shader
	
	// No specular material for scenelight
	const SceneLight scenelight = *m_light_resource.get_scenelight("standard_scenelight");
	shader_program->set_uniform("scenelight.ambient", scenelight.m_ambient);
	shader_program->set_uniform("scenelight.diffuse", scenelight.m_diffuse);

	shader_program->attach_directional_light(*m_light_resource.get_dirlight("standard_dirlight"));
	shader_program->attach_point_light(*m_light_resource.get_pointlight("standard_pointlight"));

	// TODO attach texture map here using the shader attach texture function
	m_voxel_range_data = VoxelMetaData{ id, x_range, y_range, z_range };
}

VoxelMetaData SceneLoader::get_voxel_metadata() const{
	return m_voxel_range_data;
}
