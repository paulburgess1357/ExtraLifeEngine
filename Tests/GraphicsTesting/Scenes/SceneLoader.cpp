#include "SceneLoader.h"
#include "../../ECS/Components/IncludeComponents.h"
#include "../../ResourceManagement/IncludeResources.h"

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

void SceneLoader::load_scene(entt::registry& registry) {

	// voxels(registry, 7, 3, 7);	
	// grid(registry);
	// single_cube(registry);
	// single_cube_textured(registry);
	// load_backpack(registry);
	load_spartan(registry);
	// cubemap(registry);
	// load_framebuffer(registry);
	
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
	shader_program->attach_directional_light(*m_light_resource.get_dirlight("standard_dirlight1"));

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

	const PointLight pointlight{ "backpack_pointlight_test", glm::vec3{6.0f, 0.0f, 0.0f }, 1.0f, 0.09f, 0.032f };
	m_light_resource.load(pointlight);
	shader_program->attach_point_light(pointlight);
	
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
	m_shader_resource.load(id, "Assets/shaders/model_shaders/spartan/spartan_vertex.glsl", "Assets/shaders/model_shaders/spartan/spartan_fragment.glsl", true);
	IShaderProgram* shader_program = m_shader_resource.get(id);

	m_model_resource.load(id, "Assets/models/spartan/scene.gltf", *shader_program, m_texture_resource, true);

	// Note: No specular material in spartan, so we must manually load the scene light (it has a specular property)
	// Note2: I'm also making the impact of light higher by adjusting the scenelight diffuse property
	SceneLight* scene_light = m_light_resource.get_scenelight("standard_scenelight1");
	scene_light->m_diffuse = glm::vec3(1.9f);
	shader_program->set_uniform("scenelight.ambient", scene_light->m_ambient);
	shader_program->set_uniform("scenelight.diffuse", scene_light->m_diffuse);

	//const DirectionalLight dirlight{"spartan_dirlight_test", glm::vec3{0.5f, 0.5f, 0.0f } };
	//m_light_resource.load(dirlight);
	//shader_program->attach_directional_light(dirlight);
	
	const PointLight pointlight{ "spartan_pointlight_test", glm::vec3{-8.0f, 125.0f, 30.0f }, 1.0f, 0.0009f, 0.000032f };
	m_light_resource.load(pointlight);
	shader_program->attach_point_light(pointlight);

	const entt::entity model_entity = registry.create();
	registry.emplace<ModelComponent>(model_entity, m_model_resource.get(id));
	registry.emplace<TransformComponent>(model_entity, glm::vec3{ -4.0f, 0.0f, 0.0f });
	registry.emplace<ShaderComponent>(model_entity, shader_program);
	registry.emplace<RotationComponent>(model_entity, 0.0f, 0.009f, 0.0f, 0.0f);	
}

void SceneLoader::load_framebuffer(entt::registry& registry) const{
	m_shader_resource.load("framebuffer_shader", "Assets/shaders/framebuffer_shaders/framebuffer_vertex.glsl", "Assets/shaders/framebuffer_shaders/framebuffer_fragment_edge.glsl", false);
	IShaderProgram* shader_program = m_shader_resource.get("framebuffer_shader");

	// Binding the sampler2d screen_quad to tex unit 0 (framebuffer only has one texture)
	shader_program->set_uniform("screen_quad", 0);
		
	const entt::entity model_entity = registry.create();
	registry.emplace<ShaderComponent>(model_entity, shader_program);
	registry.emplace<FrameBufferComponent>(model_entity, &m_framebuffer);
}

void SceneLoader::cubemap(entt::registry& registry) const{

	const std::string id = "space_red";
	m_shader_resource.load(id, "Assets/shaders/cubemap_shaders/cubemap_vertex.glsl", "Assets/shaders/cubemap_shaders/cubemap_fragment.glsl", true);
	IShaderProgram* shader_program = m_shader_resource.get(id);

	m_texture_resource.load_cubemap_textures(id, "Assets/cubemaps/space_red");
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
	const SceneLight custom_scenelight{ "voxel_scenelight_test", glm::vec3 { 0.6f }, glm::vec3 { 0.9f }, glm::vec3 { 1.0f } };
	m_light_resource.load(custom_scenelight);
	shader_program->set_uniform("scenelight.ambient", custom_scenelight.m_ambient);
	shader_program->set_uniform("scenelight.diffuse", custom_scenelight.m_diffuse);

	// shader_program->attach_directional_light(*m_light_resource.get_dirlight("standard_dirlight1"));
	const PointLight pointlight{ "voxel_pointlight_test", glm::vec3{0.0f, 20.0f, 0.0f }, 1.0f, 0.0014f, 0.000007f };
	m_light_resource.load(pointlight);
	shader_program->attach_point_light(pointlight);

	// TODO attach texture map here using the shader attach texture function
	m_voxel_range_data = VoxelMetaData{ id, x_range, y_range, z_range };
}

VoxelMetaData SceneLoader::get_voxel_metadata() const{
	return m_voxel_range_data;
}
