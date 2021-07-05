#include "ITexture.h"

ITexture::ITexture(const unsigned int handle, std::string texture_name)
	:m_handle{ handle },
	m_texture_name{ std::move(texture_name) }{
}

unsigned int ITexture::get_handle() const{
	return m_handle;
}

std::string ITexture::get_texture_name() const{
	return m_texture_name;
}
