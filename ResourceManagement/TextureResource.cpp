#include "TextureResource.h"
#include "../Environment/Interfaces/Texture/ITextureLoader.h"
#include "../Environment/Neutral/Texture/TextureLoaderFromFile.h"
#include "../Environment/OpenGL/Texture/OpenGLTextureCompiler.h"
#include "../Utility/Print.h"
#include "../Utility/FatalError.h"

std::unordered_map<std::string, std::shared_ptr<ITexture>> TextureResource::m_texture_cache;

std::shared_ptr<ITexture> TextureResource::load(const std::string& texture_name, const std::string& texture_path, const bool flip_texture){
	
	if (!is_loaded(texture_name)) {
		Print::print("\nLoading Texture: " + texture_name + " (" + texture_path + ")");
		const std::shared_ptr<ITextureLoader> texture_loader = std::make_shared<TextureLoaderFromFile>(texture_path, flip_texture);
		const std::shared_ptr<ITextureCompiler> texture_compiler = ITextureCompiler::create_compiler(texture_loader);
		m_texture_cache[texture_name] = texture_compiler->compile();		
	}
	return m_texture_cache[texture_name];	
}

std::shared_ptr<ITexture> TextureResource::load(const std::string& texture_path, const bool flip_texture){
	return load(texture_path, texture_path, flip_texture);
}

bool TextureResource::is_loaded(const std::string& texture_name) {
	const auto it = m_texture_cache.find(texture_name);
	if (it == m_texture_cache.end()) {
		return false;
	}
	return true;
}

std::shared_ptr<ITexture> TextureResource::get(const std::string& texture_name) {
	if (!is_loaded(texture_name)) {
		FatalError::fatal_error("Unable to locate texture: " + texture_name);
	}
	return m_texture_cache.at(texture_name);
}

void TextureResource::destroy(const std::string& texture_name){
	if (!is_loaded(texture_name)) {
		FatalError::fatal_error("Unable to locate and destroy texture: " + texture_name);
	}
	Print::print("Destroying Texture: " + texture_name);
	m_texture_cache.at(texture_name)->destroy();
	m_texture_cache.erase(texture_name);
}

void TextureResource::destroy_all(){
	for (auto& texture : m_texture_cache) {
		Print::print("Destroying Texture: " + texture.first);
		texture.second->destroy();
	}
	m_texture_cache.clear();
}