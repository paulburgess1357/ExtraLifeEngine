#pragma once
#include "../Neutral/WorldPosition.h"
#include "../../Camera/Camera.h"
#include <vector>

class ChunkInRange{

public:
	static void set_chunks_in_range(const Camera& camera);
	static std::vector<WorldPosition> get_chunks_in_range();
	
private:
	static std::vector<WorldPosition> get_chunks_in_range(const WorldPosition& base_position);

	static int m_range_qty;
	static std::vector<WorldPosition> m_chunks_in_camera_range;
};

