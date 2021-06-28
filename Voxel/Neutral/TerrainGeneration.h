#pragma once
#include <noise/noise.h>
#include "../../World/WorldPosition.h"

class TerrainGeneration{
	
public:
	static int generate_top_layer(const WorldPosition& starting_world_position, const int x_local, const int z_local, const int x_block_qty, const int y_block_qty, const int z_block_qty);
	static int generate_top_layer2(const WorldPosition& starting_world_position, const int x_local, const int z_local, const int x_block_qty, const int y_block_qty, const int z_block_qty);

private:
	static noise::module::Perlin m_perlin_noise;
	
	static double generate_noise(const double nx, const double nz);
	
};

