#pragma once
#include "IModel.h"
#include "../Loader/OpenGLModelLoaderFromFile.h"
#include "../Mesh/OpenGLMesh.h"
#include <vector>

namespace OpenGL{

	class OpenGLModel : public IModel {

	public:
		OpenGLModel(OpenGLModelLoaderFromFile& model_loader, const std::shared_ptr<IShaderProgram>& shader_program);
		~OpenGLModel() = default;		
		void draw() const override;
		void destroy() override;
		
	private:		
		std::vector<OpenGLMesh> m_mesh_vector;
	};
	
} // namespace OpenGL