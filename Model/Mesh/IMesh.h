#pragma once
#include "../Vertex.h"
#include "../../Environment/Interfaces/Texture/ITexture.h"
#include "../../Environment/Interfaces/Texture/ITextureHandler.h"
#include <memory>

class IMesh{
	
public:
	IMesh(std::vector<Vertex> vertices, std::vector<unsigned> indices);
	virtual ~IMesh() = default;
	virtual void destroy() = 0;

	[[nodiscard]] size_t get_indices_size() const;
	[[nodiscard]] virtual unsigned int get_vao() const = 0;

	virtual void attach_diffuse_texture(const ITexture& texture) = 0;
	virtual void attach_normal_texture(const ITexture& texture) = 0;
	virtual void attach_specular_texture(const ITexture& texture, const float shininess = 16.0f) = 0;

	[[nodiscard]] std::shared_ptr<ITextureHandler> get_texture_handler() const;
	
protected:
	std::shared_ptr<ITextureHandler> m_texture_handler;	
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	
};
