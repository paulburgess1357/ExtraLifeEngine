#pragma once

//#define SCX 16
//#define SCY 16
//#define SCZ 16

#include "OpenGLChunk.h"
#include "../Utility/Vector3D.h"
#include <vector>

namespace OpenGL{

	class OpenGLChunkManager {

	public:
		OpenGLChunkManager() = default;
		~OpenGLChunkManager() = default;

		OpenGLChunk get(const size_t index);
		
		
		
	private:
		Vector3D<OpenGLChunk> m_chunks;

		int m_width;
		int m_height;
		int m_depth;
		
	};
	
} // namespace OpenGL



// (x,y,z) <-> z*(DIM_Y*DIM_X) + y*DIM_X + x;


