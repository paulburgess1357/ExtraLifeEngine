#pragma once
#include "GameState.h"
#include "../Camera/Camera.h"
#include "../Input/Processing/InputHandler.h"
#include "../Input/Processing/MouseHandler.h"
#include "../Environment/Interfaces/Window/IWindow.h"
#include "../Environment/Interfaces/Shader/IShaderUniformBlock.h"
#include "../ECS/Systems/Render/Interfaces/IncludeRenderers.h"
#include "../ECS/Systems/Voxel/IVoxelUpdater.h"
#include "entt/entity/registry.hpp"
#include <memory>

class GameManager {
	
public:
	GameManager();
	~GameManager();
	void set_game_state(GameState gamestate);
	void run();
	
private:
	void initialize_window();
	void initialize_imgui();
	void initialize_uniform_block_handler();
	void initialize_projection_matrix() const;
	void initialize_controls();
	void initialize_scene();
	void initialize_renderers();
	void initialize_updaters();
	
	void gameloop();
	void update();
	void render();
	void destroy() const;	
	
	GameState m_gamestate;
	entt::registry m_registry;
	std::shared_ptr<IWindow> m_window;
	Camera m_camera;
	InputHandler m_input_handler;
	MouseHandler m_mouse_handler;

    std::shared_ptr<IShaderUniformBlock> m_shader_uniform_block_handler = nullptr;	
	std::shared_ptr<ICubeRenderer> m_cube_renderer = nullptr;	
	std::shared_ptr<IModelRenderer> m_model_renderer = nullptr;
	std::shared_ptr<ICubeMapRenderer> m_cubemap_renderer = nullptr;
	std::shared_ptr<IVoxelRenderer> m_voxel_renderer = nullptr;

	std::shared_ptr<IVoxelUpdater> m_voxel_updater = nullptr;
};


