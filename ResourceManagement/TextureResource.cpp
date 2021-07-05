#include "TextureResource.h"
#include "../Environment/Interfaces/Texture/ITextureLoader.h"
#include "../Environment/Interfaces/Texture/ITextureCompiler.h"
#include "../Environment/Interfaces/Texture/ICubeMapCompiler.h"
#include "../Environment/Neutral/Texture/TextureLoaderFromFile.h"
#include "../Utility/Print.h"
#include "../Utility/FatalError.h"

TextureResource::~TextureResource(){
	destroy_all();
}

void TextureResource::load(const std::string& texture_name, const std::string& texture_path, const bool flip_texture){	
	if (!is_loaded(texture_name)) {
		Print::print("\nLoading Texture: " + texture_name + " (" + texture_path + ")");
		const std::shared_ptr<ITextureLoader> texture_loader = std::make_shared<TextureLoaderFromFile>(texture_name, texture_path, flip_texture);
		const std::shared_ptr<ITextureCompiler> texture_compiler = ITextureCompiler::create_compiler(texture_loader);
		m_texture_cache[texture_name] = texture_compiler->compile();		
	}
}

void TextureResource::load_model_textures(const std::string& texture_path, const bool flip_texture){
	return load(texture_path, texture_path, flip_texture);
}

void TextureResource::load_cubemap_textures(const std::string& cubemap_name, const std::string& cubemap_folder, const bool flip_textures){
	if(!is_loaded(cubemap_name)){
		Print::print("\nLoading CubeMap: " + cubemap_name + " (" + cubemap_folder + ")");
		std::shared_ptr<ITextureLoader> texture_loader = std::make_shared<TextureLoaderFromFile>(cubemap_name, cubemap_folder, flip_textures);
		std::unordered_map<std::string, std::shared_ptr<ITextureLoader>> texture_loaders = texture_loader->create_cubemap_loader();		
		const std::shared_ptr<ICubeMapCompiler> cubemap_compiler = ICubeMapCompiler::create_compiler(texture_loaders);
		m_texture_cache[cubemap_name] = cubemap_compiler->compile(cubemap_name);
	}
}

bool TextureResource::is_loaded(const std::string& texture_name) const{
	return m_texture_cache.count(texture_name) > 0;
}

ITexture* TextureResource::get(const std::string& texture_name) {
	if (!is_loaded(texture_name)) {
		FatalError::fatal_error("Unable to locate texture: " + texture_name);
	}
	return m_texture_cache.at(texture_name).get();
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
	Print::print("Destroying TextureResource");
	for (auto& texture : m_texture_cache) {
		Print::print("        - Destroying Texture: " + texture.first);
		texture.second->destroy();
	}
	m_texture_cache.clear();
}
