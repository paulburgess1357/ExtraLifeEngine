#pragma once
#include "../Interfaces/IVoxelRenderer.h"

namespace OpenGL{

	class OpenGLVoxelRenderer : public IVoxelRenderer {
	public:
		void render() const override;		
	};
	
} // namespace OpenGL