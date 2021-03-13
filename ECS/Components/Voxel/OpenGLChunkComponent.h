#pragma once
#include "../../Voxel/OpenGL/OpenGLChunk.h"
#include <memory>

namespace OpenGL {

	struct OpenGLChunkComponent {
		OpenGLChunkComponent()
			:m_chunk(nullptr) {
		}

		OpenGLChunkComponent(std::shared_ptr<OpenGLChunk>& chunk)
			:m_chunk{ chunk } {
		}

		std::shared_ptr<OpenGLChunk> m_chunk = nullptr;
	};
	
} // namespace OpenGL


