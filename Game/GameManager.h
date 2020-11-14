#pragma once
#include "GameState.h"
#include "../Camera/Camera.h"
#include "../Input/Processing/InputHandler.h"
#include "../Input/Processing/MouseHandler.h"
#include "../Environment/Neutral/Window/Window.h"
#include "../Environment/Interfaces/Shader/IShaderUniformBlock.h"
#include "../ECS/Systems/Render/Interfaces/ICubeRenderer.h"
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
	void initialize_uniform_blocks();
	void initialize_projection_matrix() const;
	void initialize_controls();
	void initialize_scene();
	void initialize_renderers();	
	
	void gameloop();
	void update();
	void render();
	void destroy() const;		
	
	GameState m_gamestate;
	entt::registry m_registry;
	std::shared_ptr<Window> m_window;
	Camera m_camera;
	InputHandler m_input_handler;
	MouseHandler m_mouse_handler;		

	std::shared_ptr<IShaderUniformBlock> m_shader_uniform_block = nullptr;	
	std::shared_ptr<ICubeRenderer> m_cube_renderer = nullptr;	
	
};


