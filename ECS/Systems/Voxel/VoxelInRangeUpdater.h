#pragma once
#include "../../Camera/Camera.h"

class VoxelInRangeUpdater{
	
public:
	static void set_all_chunks_in_range(const Camera& camera, const int range);
};

