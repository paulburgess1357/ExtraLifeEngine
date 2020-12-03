#pragma once
#include "ICubeLoader.h"
#include <utility>

namespace OpenGL{

	class OpenGLCubeLoader : public ICubeLoader {

	public:
		[[nodiscard]] std::pair<unsigned int, unsigned int> load_cube_verticies() const override;
		[[nodiscard]] std::pair<unsigned int, unsigned int> load_cube_normal_verticies() const override;
		[[nodiscard]] virtual std::pair<unsigned int, unsigned int> load_cube_textured_verticies() const override;
		[[nodiscard]] std::pair<unsigned int, unsigned int> load_cube_normal_textured_verticies() const override;
		[[nodiscard]] std::pair<unsigned int, unsigned int> load_cubemap_verticies() const override;
		void destory(const unsigned int vbo_id, const unsigned int vao_id) const override;
	};
	
} // namespace OpenGL


