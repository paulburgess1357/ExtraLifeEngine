#include "ITexture.h"

ITexture::ITexture(const unsigned int handle)
	:m_handle{ handle } {
}

[[nodiscard]] unsigned int ITexture::get_handle() const{
	return m_handle;
}