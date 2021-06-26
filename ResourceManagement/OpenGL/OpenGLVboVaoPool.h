#pragma once
#include "../IVboVaoPool.h"

namespace OpenGL{

	class OpenGLVboVaoPool : public IVboVaoPool{
	public:
		OpenGLVboVaoPool() = default;
		std::shared_ptr<IVboVaoPool> get_instance() override;
		std::pair<unsigned, unsigned> get_resource() override;
		void return_resource(std::pair<unsigned, unsigned> resource) override;
	};	
	
} // namespace OpenGL