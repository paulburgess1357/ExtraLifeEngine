#pragma once
#include <string>

class ITexture{
	
public:
	ITexture(const unsigned int handle, std::string texture_name);
	
	virtual ~ITexture() = default;
	virtual void destroy() const = 0;	
	
	[[nodiscard]] unsigned int get_handle() const;
	[[nodiscard]] std::string get_texture_name() const;
	
protected:
	unsigned int m_handle;
	std::string m_texture_name;
	
};
