#include "VoxelResource.h"
#include "GraphicsConstants.h"
#include "../Voxel/OpenGL/OpenGLChunk.h"
#include "../Utility/Print.h"
#include "../Utility/FatalError.h"
#include "../Environment/Neutral/API/GraphicsAPI.h"
#include <utility>

VoxelResource::VoxelResource()
	:m_vao_vbo_pool{ IVboVaoPool::create_vbo_vao_pool() }{
}

VoxelResource::~VoxelResource(){
	destroy_all();
}

Chunk* VoxelResource::get_chunk(const WorldPosition& world_position) const{
	return m_chunkmap.at(world_position).get();
}

std::unordered_map<WorldPosition, std::unique_ptr<Chunk>, WorldPositionHash>& VoxelResource::get_chunkmap() {
	return m_chunkmap;
}

void VoxelResource::load_xyz_chunk_range(const int x_chunk_qty, const int y_chunk_qty, const int z_chunk_qty) {

	// As chunks are loaded they check chunks next to them and draw vertices
	// based on the adjacent chunk values.  This means that the chunk variable
	// 'm_block_types' must be loaded prior to the graphics data being loaded
	// in the update function.

	for (int x = 0; x < x_chunk_qty; x++) {
		for (int y = 0; y < y_chunk_qty; y++) {
			for (int z = 0; z < z_chunk_qty; z++) {				
				load_individual_chunk(WorldPosition{ x * x_block_qty, y * y_block_qty, z * z_block_qty });
			}
		}
	}

	set_all_chunk_neighbors();
}

void VoxelResource::load_individual_chunk(const WorldPosition& world_position) {

	if (GraphicsAPI::get_api() == GraphicsAPIType::OPENGL) {
		std::pair<unsigned int, unsigned int> vbo_vao = m_vao_vbo_pool->get_resource();
		m_chunkmap[world_position] = std::make_unique<OpenGL::OpenGLChunk>(world_position, vbo_vao.first, vbo_vao.second);
		return;
	}

	if (GraphicsAPI::get_api() == GraphicsAPIType::VULKAN) {
		FatalError::fatal_error("Vulkan chunk type does not exist!.");
		return;
	}

	FatalError::fatal_error("Unknown graphics API type.  Cannot create chunk for chunk manager.");
}

void VoxelResource::load_multiple_chunks(const std::vector<WorldPosition>& world_positions) {
	for (const auto& world_position : world_positions) {
		load_individual_chunk(world_position);
	}
}

void VoxelResource::set_all_chunk_neighbors() const{

	// Each individual chunk is surrounded by neighbors.  This sets
	// pointers inside each chunk towards its neighbors

	for (auto& chunk : m_chunkmap) {
		set_individual_chunk_neighbors(*get_chunk(chunk.first));
		chunk.second->set_update_required(true);
	}
}

void VoxelResource::set_specific_chunk_neighbors(const std::vector<WorldPosition>& chunk_positions) const{
	for(const auto& position : chunk_positions){
		if(m_chunkmap.count(position) != 0){

			// Both the current chunk and the neighboring chunks need to be
			// updated.

			// - New chunks will add the existing old chunk neighbors AND new
			//   chunk neighbors
			// - Old chunks will be updated to add the new chunk neighbors
			// - Both old and new chunks will have 'update_required' set to
			//   true, so the verticies sent to the GPU will be updated			
			
			// Current Chunk
			Chunk* chunk = get_chunk(position);
			set_individual_chunk_neighbors(*chunk);
			chunk->set_update_required(true);

			// Left
			Chunk* left_chunk = chunk->get_left_adjacent_chunk();
			if(left_chunk != nullptr){
				set_individual_chunk_neighbors(*left_chunk);
				left_chunk->set_update_required(true);
			}

			// Right 
			Chunk* right_chunk = chunk->get_right_adjacent_chunk();
			if(right_chunk != nullptr){
				set_individual_chunk_neighbors(*right_chunk);
				right_chunk->set_update_required(true);
			}

			// Top
			Chunk* top_chunk = chunk->get_top_adjacent_chunk();
			if(top_chunk != nullptr){
				set_individual_chunk_neighbors(*top_chunk);
				top_chunk->set_update_required(true);
			}
			
			// Bottom
			Chunk* bottom_chunk = chunk->get_bottom_adjacent_chunk();
			if(bottom_chunk != nullptr){
				set_individual_chunk_neighbors(*bottom_chunk);
				bottom_chunk->set_update_required(true);
			}

			// Front
			Chunk* front_chunk = chunk->get_front_adjacent_chunk();
			if(front_chunk != nullptr){
				set_individual_chunk_neighbors(*front_chunk);
				front_chunk->set_update_required(true);
			}

			// Back
			Chunk* back_chunk = chunk->get_back_adjacent_chunk();
			if(back_chunk != nullptr){
				set_individual_chunk_neighbors(*back_chunk);
				back_chunk->set_update_required(true);
			}					
		}		
	}
}

void VoxelResource::set_individual_chunk_neighbors(Chunk& chunk) const{

	const WorldPosition world_position = chunk.get_starting_world_position();
	
	if (adjacent_chunk_exists(world_position, AdjacentChunkPosition::LEFT)) {
		Chunk* adjacent_chunk = get_adjacent_chunk(world_position, AdjacentChunkPosition::LEFT);
		chunk.set_left_adjacent_chunk(adjacent_chunk);
	}

	if (adjacent_chunk_exists(world_position, AdjacentChunkPosition::RIGHT)) {
		Chunk* adjacent_chunk = get_adjacent_chunk(world_position, AdjacentChunkPosition::RIGHT);
		chunk.set_right_adjacent_chunk(adjacent_chunk);
	}

	if (adjacent_chunk_exists(world_position, AdjacentChunkPosition::TOP)) {
		Chunk* adjacent_chunk = get_adjacent_chunk(world_position, AdjacentChunkPosition::TOP);
		chunk.set_top_adjacent_chunk(adjacent_chunk);
	}

	if (adjacent_chunk_exists(world_position, AdjacentChunkPosition::BOTTOM)) {
		Chunk* adjacent_chunk = get_adjacent_chunk(world_position, AdjacentChunkPosition::BOTTOM);
		chunk.set_bottom_adjacent_chunk(adjacent_chunk);
	}

	if (adjacent_chunk_exists(world_position, AdjacentChunkPosition::FRONT)) {
		Chunk* adjacent_chunk = get_adjacent_chunk(world_position, AdjacentChunkPosition::FRONT);
		chunk.set_front_adjacent_chunk(adjacent_chunk);
	}

	if (adjacent_chunk_exists(world_position, AdjacentChunkPosition::BACK)) {
		Chunk* adjacent_chunk = get_adjacent_chunk(world_position, AdjacentChunkPosition::BACK);
		chunk.set_back_adjacent_chunk(adjacent_chunk);
	}

}

bool VoxelResource::adjacent_chunk_exists(const WorldPosition& world_position, const AdjacentChunkPosition adjacent_chunk) const {

	bool chunk_exists_result = false;

	switch (adjacent_chunk) {

		case AdjacentChunkPosition::LEFT:
			chunk_exists_result = chunk_exists(WorldPosition(world_position.x - x_block_qty, world_position.y, world_position.z));
			break;

		case AdjacentChunkPosition::RIGHT:
			chunk_exists_result = chunk_exists(WorldPosition(world_position.x + x_block_qty, world_position.y, world_position.z));
			break;

		case AdjacentChunkPosition::TOP:
			chunk_exists_result = chunk_exists(WorldPosition(world_position.x, world_position.y + y_block_qty, world_position.z));
			break;

		case AdjacentChunkPosition::BOTTOM:
			chunk_exists_result = chunk_exists(WorldPosition(world_position.x, world_position.y - y_block_qty, world_position.z));
			break;

		case AdjacentChunkPosition::FRONT:
			chunk_exists_result = chunk_exists(WorldPosition(world_position.x, world_position.y, world_position.z + z_block_qty));
			break;

		case AdjacentChunkPosition::BACK:
			chunk_exists_result = chunk_exists(WorldPosition(world_position.x, world_position.y, world_position.z - z_block_qty));
			break;

		default:
			FatalError::fatal_error("Unknown adjacent chunk position");
		}

	return chunk_exists_result;

}

Chunk* VoxelResource::get_adjacent_chunk(const WorldPosition& world_position, const AdjacentChunkPosition adjacent_chunk) const {

	WorldPosition adjacent_world_position;

	switch (adjacent_chunk) {

		case AdjacentChunkPosition::LEFT:
			adjacent_world_position = WorldPosition(world_position.x - x_block_qty, world_position.y, world_position.z);
			break;

		case AdjacentChunkPosition::RIGHT:
			adjacent_world_position = WorldPosition(world_position.x + x_block_qty, world_position.y, world_position.z);
			break;

		case AdjacentChunkPosition::TOP:
			adjacent_world_position = WorldPosition(world_position.x, world_position.y + y_block_qty, world_position.z);
			break;

		case AdjacentChunkPosition::BOTTOM:
			adjacent_world_position = WorldPosition(world_position.x, world_position.y - y_block_qty, world_position.z);
			break;

		case AdjacentChunkPosition::FRONT:
			adjacent_world_position = WorldPosition(world_position.x, world_position.y, world_position.z + z_block_qty);
			break;

		case AdjacentChunkPosition::BACK:
			adjacent_world_position = WorldPosition(world_position.x, world_position.y, world_position.z - z_block_qty);
			break;

		default:
			FatalError::fatal_error("Unknown adjacent chunk position");
		}

	return get_chunk(adjacent_world_position);
}

bool VoxelResource::chunk_exists(const WorldPosition& world_position) const{
	return m_chunkmap.count(world_position);
}

void VoxelResource::destroy_all(){
	Print::print("Destroying VoxelResource");
	m_chunkmap.clear();
}

void VoxelResource::unload_vbo_vao_into_pool(const WorldPosition& world_position) const{
	unload_vbo_vao_into_pool(*get_chunk(world_position));
}

void VoxelResource::unload_vbo_vao_into_pool(Chunk& chunk) const{	
	const std::pair<unsigned int, unsigned int> vbo_vao = std::make_pair(chunk.get_vbo(), chunk.get_vao());	
	chunk.set_vbo(GraphicsConstants::UNINITIALIZED_VALUE);
	chunk.set_vao(GraphicsConstants::UNINITIALIZED_VALUE);
	m_vao_vbo_pool->return_resource(vbo_vao);
}

void VoxelResource::load_vbo_vao_into_chunk(const WorldPosition& world_position) const{
	Chunk* chunk = get_chunk(world_position);
	const std::pair<unsigned int, unsigned int> vbo_vao = m_vao_vbo_pool->get_resource();	
	chunk->set_vbo(vbo_vao.first);
	chunk->set_vao(vbo_vao.second);
}

bool VoxelResource::is_world_position_loaded(const WorldPosition& world_position) const{
	return m_chunkmap.count(world_position) > 0;
}
