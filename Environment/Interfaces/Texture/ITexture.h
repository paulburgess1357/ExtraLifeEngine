#pragma once

class ITexture{
	
public:
	ITexture(const unsigned int handle)
		:m_handle{ handle } {
	}
	
	virtual ~ITexture() = default;
	virtual void bind() const = 0;
	virtual void unbind() const = 0;
	virtual void destroy() const = 0;
	
	
	[[nodiscard]] unsigned int get_handle() const{
		return m_handle;
	}
	
protected:
	unsigned int m_handle;
	
};

