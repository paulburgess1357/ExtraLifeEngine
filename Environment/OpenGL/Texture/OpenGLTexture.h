#pragma once
#include "../../Interfaces/Texture/ITexture.h"
#include <string>

namespace OpenGL {

	class OpenGLTexture : public ITexture {
		
	public:
		OpenGLTexture(const unsigned int handle, std::string texture_name);
		void destroy() const override;
	};
	
} // namespace OpenGL
