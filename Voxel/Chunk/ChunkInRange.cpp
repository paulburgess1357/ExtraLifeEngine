#include "ChunkInRange.h"
#include "Chunk.h"

std::vector<WorldPosition> ChunkInRange::get_world_positions_in_range(const WorldPosition& base_position, const int range, const bool clamp_height_at_zero){
	std::vector<WorldPosition> world_positions_in_range;
	
	const int range_qty_start = range * -1;
	const int range_qty_end = range + 1;

	if(clamp_height_at_zero){
		for (int x = range_qty_start; x < range_qty_end; x++) {
			for (int z = range_qty_start; z < range_qty_end; z++) {
				world_positions_in_range.emplace_back(base_position.x + (x_block_qty * x), 0, base_position.z + (z_block_qty * z));
			}
		}
	} else{
		for (int x = range_qty_start; x < range_qty_end; x++) {
			for (int y = range_qty_start; y < range_qty_end; y++) {
				for (int z = range_qty_start; z < range_qty_end; z++) {
					world_positions_in_range.emplace_back(base_position.x + (x_block_qty * x), base_position.y + (y_block_qty * y), base_position.z + (z_block_qty * z));
				}
			}
		}
	}	

	return world_positions_in_range;
}