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

struct less_than_key_REMOVE_ME
{
	inline bool operator() (const WorldPosition& struct1, const WorldPosition& struct2)
	{
		if (struct1.x == struct2.x) {
			if (struct1.y == struct2.y) {
				return struct1.z < struct2.z;
			}
			return struct1.y < struct2.y;
		}
		return struct1.x < struct2.x;
	}
};