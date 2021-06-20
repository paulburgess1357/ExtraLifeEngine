#include "ChunkInRange.h"
#include "Chunk.h"

std::vector<WorldPosition> ChunkInRange::get_world_positions_in_range(const WorldPosition& base_position, const int x_range, const int y_range, const int z_range){
	std::vector<WorldPosition> world_positions_in_range;

	const int x_range_qty_start = x_range * -1;
	const int x_range_qty_end = x_range + 1;

	const int y_range_qty_start = y_range * -1;
	const int y_range_qty_end = y_range + 1;

	const int z_range_qty_start = z_range * -1;
	const int z_range_qty_end = z_range + 1;
	
	for (int x = x_range_qty_start; x < x_range_qty_end; x++) {
		for (int y = y_range_qty_start; y < y_range_qty_end; y++) {
			for (int z = z_range_qty_start; z < z_range_qty_end; z++) {
				world_positions_in_range.emplace_back(base_position.x + (x_block_qty * x), base_position.y + (y_block_qty * y), base_position.z + (z_block_qty * z));
			}
		}
	}

	return world_positions_in_range;
}