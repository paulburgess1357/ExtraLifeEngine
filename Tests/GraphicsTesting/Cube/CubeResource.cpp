#include "CubeResource.h"
#include "OpenGLCubeLoader.h"
#include "../../Utility/Print.h"
#include "../../Utility/FatalError.h"

std::shared_ptr<ICubeLoader> CubeResource::m_cube_loader = nullptr;

std::unordered_map<std::string, CubeIDStruct> CubeResource::m_cube_id_cache{
	{ "cube", { 99, 99, 99 } },
	{ "cube_normal", { 99, 99, 99 } },
	{ "cube_textured", { 99, 99, 99} },
	{ "cube_normal_textured", { 99, 99, 99 } },
	{ "cubemap", { 99, 99, 99 } } 
};

unsigned int CubeResource::get(const std::string& cube_name){

	if(m_cube_loader == nullptr){
		m_cube_loader = ICubeLoader::create_cube_loader();
	}
	
	load(cube_name);
	return m_cube_id_cache[cube_name].m_vao_id;
}

void CubeResource::load(const std::string& cube_name) {
	if (!is_loaded(cube_name)) {
		
		if (cube_name == "cube") {
			m_cube_id_cache[cube_name] = m_cube_loader->load_cube_verticies();
		} else if (cube_name == "cube_normal") {
			m_cube_id_cache[cube_name] = m_cube_loader->load_cube_normal_verticies();
		} else if(cube_name == "cube_textured"){
			m_cube_id_cache[cube_name] = m_cube_loader->load_cube_textured_verticies();
		} else if (cube_name == "cube_normal_textured") {
			m_cube_id_cache[cube_name] = m_cube_loader->load_cube_normal_textured_verticies();
		} else if (cube_name == "cubemap") {
			m_cube_id_cache[cube_name] = m_cube_loader->load_cubemap_verticies();
		} else {
			FatalError::fatal_error("No cube type: '" + cube_name + "' exists in the cube resource manager map!");
		}
	}
}

bool CubeResource::is_loaded(const std::string& cube_name) {	

	const auto it = m_cube_id_cache.find(cube_name);
	if (it == m_cube_id_cache.end()) {
		FatalError::fatal_error("No cube type: '" + cube_name + "' exists in the cube resource manager map!");
	}

	const CubeIDStruct cube = m_cube_id_cache[cube_name];
	if (cube.m_vao_id == 99) {
		return false;
	}
	return true;
}

void CubeResource::destroy_all(){

	for(auto& cube : m_cube_id_cache){
		if(is_loaded(cube.first)){
			Print::print("Destroying Cube: '" + cube.first + "' VBO: " + std::to_string(cube.second.m_vbo_id) + " VAO: " + std::to_string(cube.second.m_vao_id) + " EBO: " + std::to_string(cube.second.m_ebo_id));
			m_cube_loader->destroy(cube.second);
		}
	}
	m_cube_id_cache.clear();
}
