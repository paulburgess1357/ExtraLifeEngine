#pragma once
#include "Chunk.h"
#include "../Neutral/WorldPosition.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <unordered_map>

//TODO make chunk resource that I can pre-load chunks...? That way I can just load the pointer and world position
//TODO as the engine starts up, and just load from the resource when I need more?		

enum class AdjacentChunkPosition{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	FRONT,
	BACK
};

class ChunkManager {

public:
	ChunkManager() = default;
	virtual ~ChunkManager() = default;		

	void load(const int size_x, const int size_y, const int size_z, const std::shared_ptr<IShaderProgram>& shader_program);
	[[nodiscard]] std::shared_ptr<Chunk> get(const WorldPosition& world_position) const;
	
	void update() const;
	void render() const;	
		
private:
	bool chunk_exists(const WorldPosition& world_position) const;
	void load(const WorldPosition& world_position, const std::shared_ptr<IShaderProgram>& shader_program);
	bool adjacent_chunk_exists(const WorldPosition& world_position, AdjacentChunkPosition adjacent_chunk) const;
	[[nodiscard]] std::shared_ptr<Chunk> get_adjacent_chunk(const WorldPosition& world_position, AdjacentChunkPosition adjacent_chunk) const;
	void set_adjacent_chunk_addresses();
	void set_adjacent_chunk_addresses(const WorldPosition& world_position, std::shared_ptr<Chunk>& chunk) const;
	std::unordered_map<WorldPosition, std::shared_ptr<Chunk>, WorldPositionHash> m_chunkmap;
};
