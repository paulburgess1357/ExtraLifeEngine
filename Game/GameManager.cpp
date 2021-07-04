#include "GameManager.h"
#include "../Matrix/ProjectionMatrix.h"
#include "../Interface/ImGuiInterface.h"
#include "../Input/Command/ControlCommands.h"
#include "../ResourceManagement/IncludeResources.h"
#include "../Tests/GraphicsTesting/Scenes/SceneLoader.h"
#include "../Environment/Interfaces/Window/IWindowCreator.h"
#include "../ECS/Systems/Transform/TransformSystem.h"
#include "../ECS/Systems/Voxel/VoxelLoader.h"

GameManager::GameManager()
	:m_gamestate{ GameState::PLAY },
	 m_camera{ Camera{ glm::vec3(0, 5, 5), glm::vec3(0.51f, 0.0f, 0.76f), 0.008f, 0.05f} },
	 m_input_handler{ m_camera },
	 m_mouse_handler{ m_camera }{	
}

GameManager::~GameManager(){
	destroy();
}

void GameManager::set_game_state(GameState gamestate) {
	m_gamestate = gamestate;
}

void GameManager::run(){
	initialize_window();
	initialize_imgui();
	initialize_uniform_block_handler();
	initialize_projection_matrix();
	initialize_controls();
	initialize_resources();
	initialize_scene();
	initialize_updaters();
	initialize_renderers();
	gameloop();
}

void GameManager::initialize_window(){
	m_window = IWindowCreator::create_window(1920, 1080, false, true);
}

void GameManager::initialize_imgui(){
	ImGuiNS::ImGuiInterface::initialize_window(m_window);
	ImGuiNS::ImGuiInterface::initialize_camera_data(m_camera);
}

void GameManager::initialize_uniform_block_handler(){
	m_shader_uniform_block_handler = IShaderUniformBlock::create_shader_uniform_block();
}

void GameManager::initialize_projection_matrix() const{
	ProjectionMatrix::initialize_projection_matrix(m_window);
}

void GameManager::initialize_controls() {
	m_input_handler.set_exit(std::make_shared<ExitCommand>(*this));
	m_input_handler.set_mouse_control(std::make_shared<MouseControlCommmand>(m_window, m_mouse_handler));
	m_input_handler.set_wireframe_mode(std::make_shared<OpenGL::OpenGLWireFrame>());
	m_input_handler.set_imgui_display(std::make_shared<ImGuiDisplayCommand>());
}

void GameManager::initialize_resources(){
	m_voxel_resource = std::make_unique<VoxelResource>();
}

void GameManager::initialize_scene(){

	// TODO shader loader or some alternative for voxels?
	SceneLoader::voxels(m_registry);
	
	// SceneLoader::grid(m_registry);
    // SceneLoader::single_cube(m_registry);
	// SceneLoader::single_cube_textured(m_registry);
	SceneLoader::single_model(m_registry);	
	SceneLoader::cubemap(m_registry);
}

void GameManager::initialize_updaters(){	
	m_world_positions_in_range_updater = std::make_unique<WorldPositionsInRangeUpdater>(0, 0, 0, m_camera);	
	m_voxel_loader = std::make_unique<VoxelLoader>(*m_voxel_resource,  *m_world_positions_in_range_updater);
	m_voxel_updater = IVoxelUpdater::get_voxel_updater(*m_voxel_resource, *m_world_positions_in_range_updater);
}

void GameManager::initialize_renderers() {
	m_cube_renderer = ICubeRenderer::get_cube_renderer();
	m_model_renderer = IModelRenderer::get_model_renderer();
	m_cubemap_renderer = ICubeMapRenderer::get_cube_renderer();
	m_voxel_renderer = IVoxelRenderer::get_voxel_renderer(*m_voxel_resource, *m_world_positions_in_range_updater);
}

void GameManager::gameloop() {
	while (m_gamestate != GameState::EXIT && !glfwWindowShouldClose(m_window->get_glfw_ptr())) {
		m_input_handler.handle_input();
		m_mouse_handler.handle_input();
		m_window->clear_color();
		update();
		render();
		m_window->swap_buffer();
	}
}

void GameManager::update(){	
	m_shader_uniform_block_handler->update(m_camera);
	m_world_positions_in_range_updater->update_world_position_vectors(m_camera);
	m_voxel_loader->update();
	m_voxel_updater->update();
	Transform::TransformSystem::update(m_registry);
	ImGuiNS::ImGuiInterface::update();
}

void GameManager::render(){	
	m_cubemap_renderer->render(m_registry, m_camera);
	m_cube_renderer->render(m_registry);
	m_model_renderer->render(m_registry);
	m_voxel_renderer->render();
	ImGuiNS::ImGuiInterface::render();
}

void GameManager::destroy() const {
	ImGuiNS::ImGuiInterface::destroy();
	ShaderResource::destroy_all();
	TextureResource::destroy_all();
	CubeResource::destroy_all();
	LightResource::destroy_all();
	ModelResource::destroy_all();
	// m_voxel_resource->destroy_all(); // Called when out of scope
	m_shader_uniform_block_handler->destroy();
	glfwTerminate();
}