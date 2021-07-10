#pragma once
#include "GameState.h"
#include "../Camera/Camera.h"
#include "../Matrix/ProjectionMatrix.h"
#include "../Input/Processing/InputHandler.h"
#include "../Input/Processing/MouseHandler.h"
#include "../Environment/Interfaces/Window/IWindow.h"
#include "../Environment/Interfaces/Framebuffer/IFrameBuffer.h"
#include "../Environment/Interfaces/Shader/IShaderUniformBlock.h"
#include "../ResourceManagement/IncludeResources.h"
#include "../Tests/GraphicsTesting/Scenes/SceneLoader.h"
#include "../ECS/Systems/Voxel/VoxelLoader.h"
#include "../ECS/Systems/Voxel/IVoxelUpdater.h"
#include "../ECS/Systems/Render/Interfaces/IncludeRenderers.h"
#include "../ECS/Systems/Render/Interfaces/IFrameBufferRenderer.h"
#include "../World/WorldPositionsInRangeUpdater.h"
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
	void initialize_controls();
	void initialize_resources();
	void initialize_scene();
	void initialize_updaters();
	void initialize_renderers();
	void qc_checks() const;
	
	void gameloop();
	void update();
	void render();
	void destroy() const;	
	
	GameState m_gamestate;
	entt::registry m_registry;	
	Camera m_camera;
	InputHandler m_input_handler;
	MouseHandler m_mouse_handler;
		
	std::unique_ptr<IWindow> m_window = nullptr;
	std::unique_ptr<IFrameBuffer> m_framebuffer = nullptr;

	std::unique_ptr<VoxelResource> m_voxel_resource = nullptr;
	std::unique_ptr<ShaderResource> m_shader_resource = nullptr;
	std::unique_ptr<ModelResource> m_model_resource = nullptr;
	std::unique_ptr<TextureResource> m_texture_resource = nullptr;
	std::unique_ptr<LightResource> m_light_resource = nullptr;
	std::unique_ptr<CubeResource> m_cube_resource = nullptr;

	std::unique_ptr<SceneLoader> m_scene_loader = nullptr;	
	std::unique_ptr<WorldPositionsInRangeUpdater> m_world_positions_in_range_updater = nullptr;
	std::unique_ptr<VoxelLoader> m_voxel_loader = nullptr;
	std::unique_ptr<IVoxelUpdater> m_voxel_updater = nullptr;	
    std::unique_ptr<IShaderUniformBlock> m_shader_uniform_block_handler = nullptr;	

	std::unique_ptr<ICubeRenderer> m_cube_renderer = nullptr;	
	std::unique_ptr<IModelRenderer> m_model_renderer = nullptr;
	std::unique_ptr<ICubeMapRenderer> m_cubemap_renderer = nullptr;
	std::unique_ptr<IVoxelRenderer> m_voxel_renderer = nullptr;
	std::unique_ptr<IFrameBufferRenderer> m_framebuffer_renderer = nullptr;

	std::unique_ptr<ProjectionMatrix> m_projection_matrix = nullptr;
};
