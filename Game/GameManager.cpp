#include "GameManager.h"
#include "../Interface/ImGuiInterface.h"
#include "../Input/Command/ControlCommands.h"
#include "../ECS/Systems/Transform/TransformSystem.h"
#include "../Environment/Interfaces/Window/IWindowCreator.h"

GameManager::GameManager()
	:m_gamestate{ GameState::PLAY },
	m_camera{ Camera{ glm::vec3(3, 2, 8), glm::vec3(0.01f, -0.09f, -0.96f), 0.005f, 0.05f} },
	m_input_handler{ m_camera },
	m_mouse_handler{ m_camera }{
}

GameManager::~GameManager() {
	destroy();
}

void GameManager::set_game_state(GameState gamestate) {
	m_gamestate = gamestate;
}

void GameManager::run() {
	initialize_window();
	initialize_imgui();
	initialize_uniform_block_handler();
	initialize_controls();
	initialize_resources();
	initialize_scene();
	initialize_updaters();
	initialize_renderers();
	qc_checks();
	gameloop();
}

void GameManager::initialize_window() {
	m_window = IWindowCreator::create_window(1920, 1080, false, true);
	m_projection_matrix = std::make_unique<ProjectionMatrix>(*m_window);
	m_framebuffer = IFrameBuffer::create_framebuffer(*m_window);
}

void GameManager::initialize_imgui() {
	ImGuiNS::ImGuiInterface::initialize_window(*m_window);
	ImGuiNS::ImGuiInterface::initialize_camera_data(m_camera);
}

void GameManager::initialize_uniform_block_handler() {
	m_shader_uniform_block_handler = IShaderUniformBlock::create_shader_uniform_block(m_projection_matrix.get());
}

void GameManager::initialize_controls() {
	m_input_handler.set_exit(std::make_unique<ExitCommand>(*this));
	m_input_handler.set_mouse_control(std::make_unique<MouseControlCommmand>(*m_window, m_mouse_handler));
	m_input_handler.set_wireframe_mode(std::make_unique<OpenGL::OpenGLWireFrame>());
	m_input_handler.set_imgui_display(std::make_unique<ImGuiDisplayCommand>());
}

void GameManager::initialize_resources() {
	m_voxel_resource = std::make_unique<VoxelResource>();
	m_shader_resource = std::make_unique<ShaderResource>();
	m_model_resource = std::make_unique<ModelResource>();
	m_texture_resource = std::make_unique<TextureResource>();
	m_light_resource = std::make_unique<LightResource>();
	m_cube_resource = std::make_unique<CubeResource>();
}

void GameManager::qc_checks() const{
	m_shader_resource->display_initialized_shader_variables();
}

void GameManager::initialize_scene() {
	m_scene_loader = std::make_unique<SceneLoader>(*m_shader_resource, *m_model_resource,
		*m_texture_resource, *m_light_resource, *m_cube_resource, *m_framebuffer);
	m_scene_loader->load_scene(m_registry);
}

void GameManager::initialize_updaters() {
	// m_world_positions_in_range_updater = std::make_unique<WorldPositionsInRangeUpdater>(0, 0, 0, m_camera);
	// m_voxel_loader = std::make_unique<VoxelLoader>(*m_voxel_resource, *m_world_positions_in_range_updater);
	// m_voxel_updater = IVoxelUpdater::get_voxel_updater(*m_voxel_resource, *m_world_positions_in_range_updater);
}

void GameManager::initialize_renderers() {
	m_cube_renderer = ICubeRenderer::get_cube_renderer();
	m_model_renderer = IModelRenderer::get_model_renderer();
	m_cubemap_renderer = ICubeMapRenderer::get_cube_renderer();
	// m_voxel_renderer = IVoxelRenderer::get_voxel_renderer(*m_voxel_resource, *m_world_positions_in_range_updater, *m_shader_resource->get("voxel_shader"));
	m_framebuffer_renderer = IFrameBufferRenderer::get_framebuffer_renderer();
}

void GameManager::gameloop() {
	while (m_gamestate != GameState::EXIT && !glfwWindowShouldClose(m_window->get_glfw_ptr())) {
		m_input_handler.handle_input();
		m_mouse_handler.handle_input();
		update();
		render();
		m_window->swap_buffer();
	}
}

void GameManager::update() {
	m_shader_uniform_block_handler->update(m_camera);
	// m_world_positions_in_range_updater->update_world_position_vectors(m_camera);
	// m_voxel_loader->update();
	// m_voxel_updater->update();
	Transform::TransformSystem::update(m_registry);
	ImGuiNS::ImGuiInterface::update();
}

void GameManager::render() {
	m_window->clear_buffers();
	m_framebuffer_renderer->start_render(m_registry);	
	m_cube_renderer->render(m_registry);
	m_model_renderer->render(m_registry);
	// m_voxel_renderer->render();
	m_cubemap_renderer->render(m_registry, m_camera);
	m_framebuffer_renderer->end_render(m_registry);
	ImGuiNS::ImGuiInterface::render();
}

void GameManager::destroy() const {
	ImGuiNS::ImGuiInterface::destroy();
	m_shader_uniform_block_handler->destroy();
	m_framebuffer->destroy();
	glfwTerminate();
}
