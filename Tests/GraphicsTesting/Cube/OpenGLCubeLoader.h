#pragma once
#include "ICubeLoader.h"
#include "CubeIDStruct.h"

namespace OpenGL{

	class OpenGLCubeLoader : public ICubeLoader {

	public:
		[[nodiscard]] CubeIDStruct load_cube_verticies() const override;
		[[nodiscard]] CubeIDStruct load_cube_normal_verticies() const override;
		[[nodiscard]] CubeIDStruct load_cube_textured_verticies() const override;
		[[nodiscard]] CubeIDStruct load_cube_normal_textured_verticies() const override;
		[[nodiscard]] CubeIDStruct load_cubemap_verticies() const override;
		void destroy(const CubeIDStruct cube_id_struct) const override;
	};
	
} // namespace OpenGL
