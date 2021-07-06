#pragma once
#include "ICubeLoader.h"
#include "CubeIDStruct.h"
#include <memory>
#include <unordered_map>

class CubeResource {

public:
	CubeResource();
	~CubeResource();
	unsigned int get(const std::string& cube_name);
	void destroy_all();

private:	
	void init_cube_cache();
	void load(const std::string& cube_name);
	bool is_loaded(const std::string& cube_name) const;	

	std::unordered_map<std::string, CubeIDStruct> m_cube_id_cache;
	std::unique_ptr<ICubeLoader> m_cube_loader;	
};
