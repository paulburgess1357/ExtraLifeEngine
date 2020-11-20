#include "LightResource.h"
#include "../Utility/Print.h"
#include "../Utility/FatalError.h"

std::unordered_map<std::string, std::shared_ptr<DirectionalLight>> LightResource::m_dirlight_cache;
std::unordered_map<std::string, std::shared_ptr<PointLight>> LightResource::m_pointlight_cache;

std::shared_ptr<DirectionalLight> LightResource::load(const std::string& light_name, const DirectionalLight& dirlight){
	m_dirlight_cache[light_name] = std::make_shared<DirectionalLight>(dirlight);
	return m_dirlight_cache[light_name];
}

std::shared_ptr<PointLight> LightResource::load(const std::string& light_name, const PointLight& pointlight) {
	m_pointlight_cache[light_name] = std::make_shared<PointLight>(pointlight);
	return m_pointlight_cache[light_name];
}

std::shared_ptr<DirectionalLight> LightResource::get_dirlight(const std::string& light_name) {
	if (!is_dirlight_loaded(light_name)) {
		FatalError::fatal_error("Unable to locate directional light: " + light_name);
	}
	return m_dirlight_cache.at(light_name);
}

bool LightResource::is_dirlight_loaded(const std::string& light_name){
	const auto it = m_dirlight_cache.find(light_name);
	if (it == m_dirlight_cache.end()) {
		return false;
	}
	return true;
}

std::shared_ptr<PointLight> LightResource::get_pointlight(const std::string& light_name) {
	if (!is_pointlight_loaded(light_name)) {
		FatalError::fatal_error("Unable to locate point light: " + light_name);
	}
	return m_pointlight_cache.at(light_name);
}

bool LightResource::is_pointlight_loaded(const std::string& light_name){
	const auto it = m_pointlight_cache.find(light_name);
	if (it == m_pointlight_cache.end()) {
		return false;
	}
	return true;
}

void LightResource::destroy_dirlight(const std::string& light_name){
	if (!is_dirlight_loaded(light_name)) {
		FatalError::fatal_error("Unable to locate and destroy directional light: " + light_name);
	}
	Print::print("Destroying Directional Light: " + light_name);
	m_dirlight_cache.erase(light_name);
}

void LightResource::destroy_pointlight(const std::string& light_name){
	if (!is_pointlight_loaded(light_name)) {
		FatalError::fatal_error("Unable to locate and destroy point light: " + light_name);
	}
	Print::print("Destroying Point Light: " + light_name);
	m_pointlight_cache.erase(light_name);
}

void LightResource::destroy_all(){
	Print::print("Destroying All Lights");
	m_dirlight_cache.clear();
	m_pointlight_cache.clear();
}