#include "GameManager.h"
#include "../Matrix/ProjectionMatrix.h"
#include "../Interface/ImGuiInterface.h"
#include "../Input/Command/ControlCommands.h"
#include "../ResourceManagement/IncludeResources.h"
#include "../ECS/Systems/Voxel/VoxelInRangeUpdater.h"
#include "../Tests/GraphicsTesting/Scenes/SceneLoader.h"
#include "../Environment/Interfaces/Window/IWindowCreator.h"
#include "../ECS/Systems/Render/OpenGL/OpenGLCubeRenderer.h"
#include "../ECS/Systems/Transform/TransformSystem.h"

GameManager::GameManager()
	:m_gamestate{ GameState::PLAY },
	m_window{ nullptr },	
	m_camera{ Camera{ glm::vec3(64, 32, 64), glm::vec3(0.0f, -0.03f, -1.0f), 0.5f, 0.05f} },
	m_input_handler{ m_camera },
	m_mouse_handler{ m_camera } {	
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
	initialize_scene();
	initialize_renderers();
	initialize_updaters();
	gameloop();
}

void GameManager::initialize_window(){
	m_window = IWindowCreator::create_window(1920, 1080, false);
}

void GameManager::initialize_imgui(){
	ImGui::ImGuiInterface::initialize(m_window);
}

void GameManager::initialize_uniform_block_handler(){
	m_shader_uniform_block_handler = IShaderUniformBlock::create_shader_uniform_block();
}

void GameManager::initialize_projection_matrix() const{
	ProjectionMatrix::initialize_projection_matrix(m_window);
}

void GameManager::initialize_controls() {
	m_input_handler.set_exit(std::make_shared<ExitCommand>(*this));
}

void GameManager::initialize_scene(){

	SceneLoader::voxels(m_registry);
	
	// SceneLoader::grid(m_registry);
    // SceneLoader::single_cube(m_registry);
	// SceneLoader::single_cube_textured(m_registry);
	// SceneLoader::single_model(m_registry);	
	SceneLoader::cubemap(m_registry);
}

void GameManager::initialize_renderers(){
	m_cube_renderer = ICubeRenderer::get_cube_renderer();
	m_model_renderer = IModelRenderer::get_model_renderer();
	m_cubemap_renderer = ICubeMapRenderer::get_cube_renderer();
	m_voxel_renderer = IVoxelRenderer::get_voxel_renderer();
}

void GameManager::initialize_updaters(){
	m_voxel_updater = IVoxelUpdater::get_voxel_updater();
}

void GameManager::gameloop() {
	while (m_gamestate != GameState::EXIT && !glfwWindowShouldClose(m_window->get_glfw_ptr())) {
		m_input_handler.hande_input();		
		m_mouse_handler.handle_input();		
		m_window->clear_color();
		update();
		render();
		m_window->swap_buffer();
	}
}

void GameManager::update(){	
	m_shader_uniform_block_handler->update(m_camera);
	VoxelInRangeUpdater::set_all_chunks_in_range(m_camera);
	m_voxel_updater->update(m_registry);
	Transform::TransformSystem::update(m_registry);
	ImGui::ImGuiInterface::update();	
}

void GameManager::render(){	
	m_cubemap_renderer->render(m_registry, m_camera);
	m_cube_renderer->render(m_registry);
	m_model_renderer->render(m_registry);
	m_voxel_renderer->render(m_registry, m_camera);
	ImGui::ImGuiInterface::render();
}

void GameManager::destroy() const {
	Print::print_separator(true, true);
	ImGui::ImGuiInterface::destroy();
	ShaderResource::destroy_all();
	TextureResource::destroy_all();
	CubeResource::destroy_all();
	LightResource::destroy_all();
	ModelResource::destroy_all();
	VoxelResource::destroy_all();
	m_shader_uniform_block_handler->destroy();
	glfwTerminate();
}