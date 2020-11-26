#pragma once

class IModel{
	
public:
	virtual ~IModel() = default;	
	virtual void draw() const = 0;
};
