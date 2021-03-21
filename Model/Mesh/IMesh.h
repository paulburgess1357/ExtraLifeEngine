#pragma once
#include "../..//Environment/Interfaces/Texture/ITextureHandler.h"
#include <string>
#include <memory>

class IMesh{
	
public:
	IMesh();
	virtual ~IMesh() = default;
	virtual void draw() const = 0;
	virtual void destroy() = 0;

	[[nodiscard]] virtual unsigned int get_vao() const = 0;
	[[nodiscard]] virtual size_t get_indices_size() const = 0;

	virtual void attach_diffuse_texture(const std::string& texture_name) = 0;
	virtual void attach_normal_texture(const std::string& texture_name) = 0;
	virtual void attach_specular_texture(const std::string& texture_name, const float shininess = 16.0f) = 0;

	std::shared_ptr<ITextureHandler> m_texture_handler;
};