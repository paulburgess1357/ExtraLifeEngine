#include "TerrainGeneration.h"
#include <iostream>
#include <cmath>

noise::module::Perlin TerrainGeneration::m_perlin_noise;

int TerrainGeneration::generate_top_layer(const WorldPosition& starting_world_position, const int x_local, const int z_local, const int x_block_qty, const int y_block_qty, const int z_block_qty){

	m_perlin_noise.SetOctaveCount(1); // 1 to 6
	m_perlin_noise.SetFrequency(1); // 1 to 16
	m_perlin_noise.SetPersistence(0); // 0 to 1
	
	const glm::vec3 start_position = starting_world_position.get_vec3();

	const double nx = (static_cast<double>(x_local + start_position.x) / x_block_qty - 0.5f);
	const double nz = (static_cast<double>(z_local + start_position.z) / z_block_qty - 0.5f);

	double noise1 = 1.0  * generate_noise(1.0 * nx, 1.0 * nz);
	double noise2 = 0.5  * generate_noise(2.0 * nx + 3.48, 2.0 * nz + 8.74);
	double noise3 = 0.25 * generate_noise(4.0 * nx + 6.81, 4.0 * nz + 1.85);

	double total_noise = (noise1 + noise2 + noise3) / (1.0 + 0.5 + 0.25);
	//total_noise = pow(total_noise, 1.2);
	total_noise = round(total_noise * y_block_qty) / y_block_qty;
	
	
	int height = total_noise * y_block_qty; // 1.0f + 0.5f + 0.25f
	// std::cout << height << std::endl;
	
	//int height = generate_noise(nx, nz) * y_block_qty; // + 2 makes tabletops			

	if (height > y_block_qty) {
		height = y_block_qty;
	}

	if (height < 1) {
		height = 1;
	}

	return height;
	
}

double TerrainGeneration::generate_noise(const double nx, const double nz){
	return m_perlin_noise.GetValue(nx, 0.0f, nz) / 2.0f + 0.5f;
}

int TerrainGeneration::generate_top_layer2(const WorldPosition& starting_world_position, const int x_local, const int z_local, const int x_block_qty, const int y_block_qty, const int z_block_qty) {

	m_perlin_noise.SetOctaveCount(1); // 1 to 6
	m_perlin_noise.SetFrequency(1); // 1 to 16
	m_perlin_noise.SetPersistence(0); // 0 to 1

	const glm::vec3 start_position = starting_world_position.get_vec3();

	const double nx = (static_cast<double>(x_local + start_position.x) / x_block_qty - 0.5f);
	const double nz = (static_cast<double>(z_local + start_position.z) / z_block_qty - 0.5f);

	double noise1 = 1.5 * generate_noise(1.0 * nx, 1.0 * nz);
	double noise2 = 0.1 * generate_noise(2.0 * nx + 3.48, 2.0 * nz + 8.74);
	double noise3 = 0.1 * generate_noise(4.0 * nx + 6.81, 4.0 * nz + 1.85);

	double total_noise = (noise1 + noise2 + noise3) / (1.0 + 0.5 + 0.25);
	//total_noise = pow(total_noise, 1.2);
	total_noise = round(total_noise * y_block_qty) / y_block_qty;


	int height = total_noise * y_block_qty; // 1.0f + 0.5f + 0.25f
	// std::cout << height << std::endl;

	//int height = generate_noise(nx, nz) * y_block_qty; // + 2 makes tabletops			

	if (height > y_block_qty) {
		height = y_block_qty;
	}

	if (height < 1) {
		height = 1;
	}

	return height;

}
