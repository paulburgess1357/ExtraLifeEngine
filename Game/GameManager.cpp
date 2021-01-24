#include "GameManager.h"
#include "../Matrix/ProjectionMatrix.h"
#include "../Input/Command/ControlCommands.h"
#include "../Interface/ImGuiInterface.h"
#include "../ResourceManagement/ModelResource.h"
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
	m_camera{ Camera{ glm::vec3(0.0f, 0, -2.0f), glm::vec3(0.0f, -0.3f, -1.0f), 0.0029f, 0.05f} },
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
	gameloop();
}

void GameManager::initialize_window(){
	m_window = IWindowCreator::create_window(1920, 1080, false);
}

void GameManager::initialize_imgui(){
	ImGuiInterface::initialize(m_window);
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
	//SceneLoader::grid(m_registry);
    //SceneLoader::single_cube(m_registry);
	//SceneLoader::single_cube_textured(m_registry);
	//SceneLoader::single_model(m_registry);


	TEMP_CHUNK_MANAGER = std::make_shared<ChunkManager>();
	
	std::shared_ptr<IShaderProgram> shader_program = ShaderResource::load("voxel_shader", "Assets/shaders/voxel/vertex/cube_colored.glsl", "Assets/shaders/voxel/fragment/cube_colored.glsl");
	shader_program->set_uniform("diffuse_material.m_sampler", glm::vec3(0.2f, 0.7f, 0.31f)); // Temp for setting cube color.  This will normally be a texture.

	// Copied from scene loader to test.... ===========
	DirectionalLight dirlight;
	dirlight.m_direction = glm::vec3(-0.50f, 1.0f, 0.3f);
	LightResource::load("dirlight", dirlight);
	shader_program->attach_directional_light("dirlight");
	TEMP_CHUNK_MANAGER->load(1, 1, 1, shader_program);
	
		
	//SceneLoader::cubemap(m_registry);
}

void GameManager::initialize_renderers(){
	m_cube_renderer = ICubeRenderer::get_cube_renderer();
	m_model_renderer = IModelRenderer::get_model_renderer();
	m_cubemap_renderer = ICubeMapRenderer::get_cube_renderer();
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
	Transform::TransformSystem::update(m_registry);	
	TEMP_CHUNK_MANAGER->update();
	ImGuiInterface::update();
}

void GameManager::render(){	
	m_cubemap_renderer->render(m_registry, m_camera);
	m_cube_renderer->render(m_registry);
	m_model_renderer->render(m_registry);
	TEMP_CHUNK_MANAGER->render();
	ImGuiInterface::render();
}

void GameManager::destroy() const {
	Print::print_separator(true, true);
	ImGuiInterface::destroy();
	ShaderResource::destroy_all();
	TextureResource::destroy_all();
	CubeResource::destroy_all();
	LightResource::destroy_all();
	ModelResource::destroy_all();	
	m_shader_uniform_block_handler->destroy();
	glfwTerminate();
}