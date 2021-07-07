#include "IMesh.h"

IMesh::IMesh(std::vector<Vertex> vertices, std::vector<unsigned> indices)
	:m_texture_handler(nullptr),
	 m_vertices{ std::move(vertices) },
	 m_indices{ std::move(indices) }{
}

size_t IMesh::get_indices_size() const {
	return m_indices.size();
}

std::shared_ptr<ITextureHandler> IMesh::get_texture_handler() const{
	return m_texture_handler;
}
