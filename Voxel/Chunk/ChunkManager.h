#pragma once
#include "Chunk.h"
#include "../Neutral/WorldPosition.h"
#include "../Neutral/AdjacentChunkPosition.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <unordered_map>

class ChunkManager {

public:
	ChunkManager() = default; 
	~ChunkManager() = default;		

	void load_all_chunks(const int x_chunk_qty, const int y_chunk_qty, const int z_chunk_qty); // Resource
	[[nodiscard]] std::shared_ptr<Chunk> get_chunk(const WorldPosition& world_position) const;	// Resource

	void update() const;
	//void render() const;	
		
private:
	void load_individual_chunk(const WorldPosition& world_position);		

	[[nodiscard]] std::shared_ptr<Chunk> get_adjacent_chunk(const WorldPosition& world_position, const AdjacentChunkPosition adjacent_chunk) const; // Resource
	[[nodiscard]] bool adjacent_chunk_exists(const WorldPosition& world_position, AdjacentChunkPosition adjacent_chunk) const; // Resource
	[[nodiscard]] bool chunk_exists(const WorldPosition& world_position) const; // Resource
	
	void set_all_chunk_neighbors(); // Resource
	void set_individual_chunk_neighbors(const WorldPosition& world_position, std::shared_ptr<Chunk>& chunk) const; // Resource
	
	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash> m_chunkmap; // Resource
};
