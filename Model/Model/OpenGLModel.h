#pragma once
#include "IModel.h"
#include "OpenGLModelLoader.h"
#include "../Mesh/OpenGLMesh.h"
#include <vector>

namespace OpenGL{

	class OpenGLModel : public IModel {

	public:
		OpenGLModel(const OpenGLModelLoader& model_loader);
		~OpenGLModel() = default;		
		void draw() const override;
		
	private:		
		std::vector<OpenGLMesh> m_mesh_vector;
	};
	
} // namespace OpenGL