#pragma once

class StencilTesting{

public:
	StencilTesting();
	virtual ~StencilTesting() = default;
	
	virtual void start_stencil_settings() const = 0;
	virtual void end_stencil_settings() const = 0;

	virtual void clear_buffer() const = 0;
	virtual void destroy() const = 0;
	
};