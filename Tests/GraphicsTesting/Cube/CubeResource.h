#pragma once
#include "ICubeLoader.h"
#include "CubeIDStruct.h"
#include <memory>
#include <unordered_map>

class CubeResource {

public:
	static unsigned int get(const std::string& cube_name);
	static void destroy_all();

private:
	CubeResource() = default;

	static void load(const std::string& cube_name);
	static bool is_loaded(const std::string& cube_name);	

	static std::unordered_map<std::string, CubeIDStruct> m_cube_id_cache;
	static std::shared_ptr<ICubeLoader> m_cube_loader;	
};
