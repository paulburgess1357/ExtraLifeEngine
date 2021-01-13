#pragma once
#include "glm/glm.hpp"

struct WorldPosition {
	WorldPosition(const int pos_x, const int pos_y, const int pos_z)
		:x{ pos_x },
		y{ pos_y },
		z{ pos_z }{
	}

	glm::vec3 get_vec3() const{
		return glm::vec3{x, y, z};
	}

	bool operator==(const WorldPosition& world_position) const{
		return world_position.x == x && world_position.y == y && world_position.z == z;
	}

	int x = 0;
	int y = 0;
	int z = 0;
};

struct WorldPositionHash{
	long operator() (const WorldPosition& world_position) const{		
		return (world_position.x * 4567 + world_position.y * 3201 + world_position.z * 21047);
	}	
};