#pragma once
#include "../../Interfaces/Texture/ITexture.h"

namespace OpenGL {

	class OpenGLTexture : public ITexture {
		
	public:
		OpenGLTexture(const unsigned int handle);
		void destroy() const override;
	};
	
} // namespace OpenGL


