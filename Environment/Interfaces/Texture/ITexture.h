#pragma once

class ITexture{
	
public:
	ITexture(const unsigned int handle);
	
	virtual ~ITexture() = default;
	virtual void destroy() const = 0;	
	
	[[nodiscard]] unsigned int get_handle() const;
	
protected:
	unsigned int m_handle;
	
};

