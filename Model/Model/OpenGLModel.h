#pragma once
#include "IModel.h"
#include "../Loader/OpenGLModelLoaderFromFile.h"

namespace OpenGL{

	class OpenGLModel : public IModel {

	public:
		OpenGLModel(OpenGLModelLoaderFromFile& model_loader);
		~OpenGLModel() = default;		
		void destroy() override;
	};
	
} // namespace OpenGL
