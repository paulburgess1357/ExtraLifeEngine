#pragma once
#include "../VboVaoPool.h"

namespace OpenGL{

	class OpenGLVboVaoPool : public VboVaoPool{
	public:
		std::shared_ptr<VboVaoPool> get_instance() override;
		std::pair<unsigned, unsigned> get_resource() override;
		std::pair<int, int> return_resource(std::pair<unsigned, unsigned> resource) override;

	private:
		OpenGLVboVaoPool() = default;
		
	};	
	
} // namespace OpenGL