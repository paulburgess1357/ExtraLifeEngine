#pragma once
#include "../Neutral/WorldPosition.h"
#include <vector>

class ChunkInRange{

public:
	static std::vector<WorldPosition> get_world_positions_in_range(const WorldPosition& base_position, const int x_range, const int y_range, const int z_range);
};