#include "OpenGLModel.h"

OpenGL::OpenGLModel::OpenGLModel(OpenGLModelLoaderFromFile& model_loader){
	m_mesh_vector = model_loader.load();	
}

void OpenGL::OpenGLModel::draw() const{
	for(const auto& mesh : m_mesh_vector){
		mesh.draw();		
	}
}

void OpenGL::OpenGLModel::destroy(){
	for (auto& mesh : m_mesh_vector){
		mesh.destroy();
	}
	m_mesh_vector.clear();
}
