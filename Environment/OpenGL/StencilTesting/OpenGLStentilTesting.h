#pragma once
#include "../../Interfaces/StencilTesting/StencilTesting.h"

namespace OpenGL{

	class OpenGLStencilTesting : public StencilTesting{
		
	public:
		OpenGLStencilTesting() = default;
		~OpenGLStencilTesting() = default;

		void start_stencil_settings() const override;
		void end_stencil_settings() const override;

		void clear_buffer() const override;
		void destroy() const override;
		
	};
	
} // namespace OpenGL
