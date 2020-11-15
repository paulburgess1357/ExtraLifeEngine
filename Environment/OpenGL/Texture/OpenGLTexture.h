#pragma once
#include "../../Interfaces/Texture/ITexture.h"
#include <string>

namespace OpenGL {

	class OpenGLTexture : public ITexture {
		
	public:
		OpenGLTexture(const unsigned int handle);

		void bind() const override;
		void unbind() const override;
		void destroy() const override;
	};
	
} // namespace OpenGL


