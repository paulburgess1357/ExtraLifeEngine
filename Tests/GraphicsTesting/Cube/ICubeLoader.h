#pragma once
#include <utility>

class ICubeLoader{
	
public:
	virtual ~ICubeLoader() = default;
	[[nodiscard]] virtual std::pair<unsigned int, unsigned int> load_cube_verticies() const = 0;	
	[[nodiscard]] virtual std::pair<unsigned int, unsigned int> load_cube_normal_verticies() const = 0;
	[[nodiscard]] virtual std::pair<unsigned int, unsigned int> load_cube_textured_verticies() const = 0;
	[[nodiscard]] virtual std::pair<unsigned int, unsigned int> load_cube_normal_textured_verticies() const = 0;
	virtual void destory(const unsigned int vbo_id, const unsigned int vao_id) const = 0;

protected:
	static const float m_cube_verticies[108];
	static const float m_cube_verticies_texture[180];
	static const float m_cube_verticies_normals[216];	
	static const float m_cube_verticies_normals_textures[288];
	
};