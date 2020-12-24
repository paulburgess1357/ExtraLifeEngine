#pragma once

class IModel{
	
public:
	IModel();
	virtual ~IModel() = default;	
	virtual void draw() const = 0;
	virtual void destroy() = 0;	
};
