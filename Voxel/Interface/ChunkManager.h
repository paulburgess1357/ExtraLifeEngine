#pragma once
#include "IChunk.h"
#include "../Neutral/WorldPosition.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <unordered_map>

//TODO make chunk resource that I can pre-load chunks...? That way I can just load the pointer and world position
//TODO as the engine starts up, and just load from the resource when I need more?		

class ChunkManager {

public:
	ChunkManager() = default;
	virtual ~ChunkManager() = default;		

	void load(const WorldPosition& m_world_position, const std::shared_ptr<IShaderProgram>& shader_program);
	void update() const;
	void render() const;

private:
	std::unordered_map<WorldPosition, std::shared_ptr<IChunk>, WorldPositionHash> m_chunkmap;
};
