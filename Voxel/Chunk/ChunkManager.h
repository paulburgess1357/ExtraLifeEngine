#pragma once
#include "Chunk.h"
#include "../Neutral/WorldPosition.h"
#include "../Neutral/AdjacentChunkPosition.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <unordered_map>

class ChunkManager {

public:
	ChunkManager() = default;
	virtual ~ChunkManager() = default;		

	void load_all_chunks(const int x_chunk_qty, const int y_chunk_qty, const int z_chunk_qty, const std::shared_ptr<IShaderProgram>& shader_program);
	[[nodiscard]] std::shared_ptr<Chunk> get_chunk(const WorldPosition& world_position) const;	

	void update() const;
	void render() const;	
		
private:
	void load_individual_chunk(const WorldPosition& world_position, const std::shared_ptr<IShaderProgram>& shader_program);		

	[[nodiscard]] std::shared_ptr<Chunk> get_adjacent_chunk(const WorldPosition& world_position, const AdjacentChunkPosition adjacent_chunk) const;
	[[nodiscard]] bool adjacent_chunk_exists(const WorldPosition& world_position, AdjacentChunkPosition adjacent_chunk) const;
	[[nodiscard]] bool chunk_exists(const WorldPosition& world_position) const;
	
	void set_all_chunk_neighbors();
	void set_individual_chunk_neighbors(const WorldPosition& world_position, std::shared_ptr<Chunk>& chunk) const;
	
	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash> m_chunkmap;
};
