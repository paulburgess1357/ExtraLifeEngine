#include "GameManager.h"
#include "../Matrix/ProjectionMatrix.h"
#include "../Input/Command/ControlCommands.h"
#include "../ResourceManagement/LightResource.h"
#include "../ResourceManagement/ShaderResource.h"
#include "../ResourceManagement/TextureResource.h"
#include "../Tests/GraphicsTesting/Cube/CubeResource.h"
#include "../Tests/GraphicsTesting/Scenes/SceneLoader.h"
#include "../Environment/Interfaces/Window/IWindowCreator.h"
#include "../ECS/Systems/Transform/TransformSystem.h"
#include "../ECS/Systems/Render/OpenGL/OpenGLCubeRenderer.h"
#include "../Environment/OpenGL/Shader/OpenGLUniformBlock.h"

GameManager::GameManager()
	:m_gamestate{ GameState::PLAY },
	m_window{ nullptr },	
	m_camera{ Camera{ glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 1.0f), .05f, 0.05f} },
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
	initialize_uniform_block_handler();
	initialize_projection_matrix();
	initialize_controls();
	initialize_scene();
	initialize_renderers();
	gameloop();
}

void GameManager::initialize_window(){
	m_window = IWindowCreator::create_window(1920, 1080, false);
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
	//SceneLoader::single_cube(m_registry);
	SceneLoader::single_cube_textured(m_registry);
}

void GameManager::initialize_renderers(){
	m_cube_renderer = ICubeRenderer::get_cube_renderer();
}

void GameManager::gameloop() {
	while (m_gamestate != GameState::EXIT && !glfwWindowShouldClose(m_window->get_glfw_ptr())) {
		m_input_handler.hande_input();
		m_mouse_handler.handle_input();
		update();
		render();
	}
}

void GameManager::update(){
	m_shader_uniform_block_handler->update(m_camera);
	Transform::TransformSystem::update(m_registry);
}

void GameManager::render(){
	m_cube_renderer->render(m_registry, m_camera);
	m_window->swap_buffer();
	m_window->clear_color();
}

void GameManager::destroy() const {
	Print::print_separator(true, true);
	ShaderResource::destroy_all();
	TextureResource::destroy_all();
	CubeResource::destroy_all();
	LightResource::destroy_all();
	m_shader_uniform_block_handler->destroy();
	glfwTerminate();
}