#pragma once
#include "VoxelSystem.h"
#include "../../ECS/Components/Voxel/ChunkComponent.h"

void Voxel::VoxelSystem::update(entt::registry& registry){

	auto view = registry.view<ChunkComponent>();

	for (auto entity : view) {
		auto& chunk = view.get<ChunkComponent>(entity);
		chunk.m_chunk->update();
	}
	
	//registry.view<ChunkComponent>().each([](auto& chunk) {
	//	chunk.m_chunk->update();
	//});
	
}
