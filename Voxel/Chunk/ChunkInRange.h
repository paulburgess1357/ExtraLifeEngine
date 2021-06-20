#pragma once
#include "../Neutral/WorldPosition.h"
#include <vector>

class ChunkInRange{

public:
	static std::vector<WorldPosition> get_world_positions_in_range(const WorldPosition& base_position, const int range, const bool clamp_height_at_zero);
};