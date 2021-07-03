#pragma once
#include "../IVboVaoPool.h"

namespace OpenGL{

	class OpenGLVboVaoPool : public IVboVaoPool{

	public:
		OpenGLVboVaoPool() = default;
		std::pair<unsigned, unsigned> get_resource() override;
		void return_resource(const std::pair<unsigned, unsigned>& resource) override;

	private:
		void check_vbo_vao_value(const std::pair<unsigned int, unsigned int>& vbo_vao) override;
		
	};	
	
} // namespace OpenGL