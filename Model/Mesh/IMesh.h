#pragma once
#include <string>

class IMesh{
public:
	virtual ~IMesh() = default;
	virtual void draw() const = 0;
	virtual void destroy() = 0;

	virtual void attach_diffuse_texture(const std::string& texture_name) = 0;
	virtual void attach_normal_texture(const std::string& texture_name) = 0;
	virtual void attach_specular_texture(const std::string& texture_name, const float shininess = 16.0f) = 0;	
};