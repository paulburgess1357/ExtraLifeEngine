#include "OpenGLModel.h"

OpenGL::OpenGLModel::OpenGLModel(OpenGLModelLoaderFromFile& model_loader){

	for(const auto& mesh : model_loader.load()){
		m_mesh_vector.push_back(std::make_unique<OpenGLMesh>(mesh));
	}
	
}

void OpenGL::OpenGLModel::destroy(){
	for (auto& mesh : m_mesh_vector){
		mesh->destroy();
	}
	m_mesh_vector.clear();
}
