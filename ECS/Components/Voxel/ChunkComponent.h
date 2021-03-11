#pragma once
#include "../../Voxel/Chunk/Chunk.h"
#include <memory>

struct ChunkComponent{
	ChunkComponent()
		:m_chunk(nullptr){		
	}

	ChunkComponent(std::shared_ptr<Chunk> chunk)
		:m_chunk{ chunk }{		
	}
	
	std::shared_ptr<Chunk> m_chunk = nullptr;
};