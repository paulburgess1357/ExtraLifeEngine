#pragma once
#include "CubeIDStruct.h"
#include <memory>

class ICubeLoader{
	
public:
	virtual ~ICubeLoader() = default;
	[[nodiscard]] virtual CubeIDStruct load_cube_verticies() const = 0;	
	[[nodiscard]] virtual CubeIDStruct load_cube_normal_verticies() const = 0;
	[[nodiscard]] virtual CubeIDStruct load_cube_textured_verticies() const = 0;
	[[nodiscard]] virtual CubeIDStruct load_cube_normal_textured_verticies() const = 0;
	[[nodiscard]] virtual CubeIDStruct load_cubemap_verticies() const = 0;
	virtual void destroy(const CubeIDStruct cube_id_struct) const = 0;

	static std::unique_ptr<ICubeLoader> create_cube_loader();

protected:

	static const int m_all_cube_ebo_indices[36];
	
	//static const float m_cube_verticies[108];
	static const float m_cube_verticies_indexed[72];	
	
	//static const float m_cube_verticies_texture[180];
	static const float m_cube_verticies_texture_indexed[120];
	
	//static const float m_cube_verticies_normals[216];
	static const float m_cube_verticies_normals_indexed[144];
	
	//static const float m_cube_verticies_normals_textures[288];
	static const float m_cube_verticies_normals_textures_indexed[192];
	
	static const float m_cubemap_verticies[108];	
};