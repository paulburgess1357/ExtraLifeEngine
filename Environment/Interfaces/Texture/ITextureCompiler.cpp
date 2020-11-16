#include "ITextureCompiler.h"

ITextureCompiler::ITextureCompiler(const std::shared_ptr<ITextureLoader>& texture_loader)
	:m_texture_loading_data{ texture_loader->load() } {
}