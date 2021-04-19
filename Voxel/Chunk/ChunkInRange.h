#pragma once
#include "../Neutral/WorldPosition.h"
#include "../../Camera/Camera.h"
#include "Chunk.h"
#include <vector>

class ChunkInRange{

public:
	static std::vector<std::shared_ptr<Chunk>> get_chunks_in_range(const Camera& camera, const int range);
	
private:	
	static WorldPosition get_nearest_chunk_coords_to_camera(const Camera& camera);
	static std::vector<WorldPosition> get_world_positions_in_range(const WorldPosition& base_position, const int range);
	static void load_chunks_in_range(const WorldPosition& base_position, const int range);	
	static void fill_chunks_in_camera_range(const std::vector<WorldPosition>& world_positions_in_range);

	static WorldPosition m_camera_chunk_coords;
	static std::vector<std::shared_ptr<Chunk>> m_chunks_in_camera_range;
	
};