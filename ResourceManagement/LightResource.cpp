#include "LightResource.h"
#include "../Utility/Print.h"
#include "../Utility/FatalError.h"

LightResource::~LightResource(){
	destroy_all();
}

void LightResource::load(const DirectionalLight& dirlight){
	m_dirlight_cache[dirlight.m_light_name] = std::make_unique<DirectionalLight>(dirlight);
}

void LightResource::load(const PointLight& pointlight) {
	check_point_light(pointlight);
	m_pointlight_cache[pointlight.m_light_name] = std::make_unique<PointLight>(pointlight);
}

void LightResource::check_point_light(const PointLight& pointlight) {
	if(pointlight.m_position.x == 0.0f && pointlight.m_position.y == 0.0f && pointlight.m_position.z == 0.0f){
		FatalError::fatal_error("Your pointlight has a position of (0,0.0).  The tangent space conversion in the normal lighting shader will be dividing by 0 during the normalization function.");
	}	
}

void LightResource::load(const SceneLight& scenelight){
	m_scenelight_cache[scenelight.m_light_name] = std::make_unique<SceneLight>(scenelight);
}

DirectionalLight* LightResource::get_dirlight(const std::string& light_name) {
	if (!is_dirlight_loaded(light_name)) {
		FatalError::fatal_error("Unable to locate directional light: " + light_name);
	}
	return m_dirlight_cache.at(light_name).get();
}

bool LightResource::is_dirlight_loaded(const std::string& light_name) const{
	return m_dirlight_cache.count(light_name) > 0;
}

PointLight* LightResource::get_pointlight(const std::string& light_name) {
	if (!is_pointlight_loaded(light_name)) {
		FatalError::fatal_error("Unable to locate point light: " + light_name);
	}
	return m_pointlight_cache.at(light_name).get();
}

bool LightResource::is_pointlight_loaded(const std::string& light_name) const{
	return m_pointlight_cache.count(light_name) > 0;
}

SceneLight* LightResource::get_scenelight(const std::string& light_name){
	if (!is_scenelight_loaded(light_name)) {
		FatalError::fatal_error("Unable to locate point light: " + light_name);
	}
	return m_scenelight_cache.at(light_name).get();
}

bool LightResource::is_scenelight_loaded(const std::string& light_name) const{
	return m_scenelight_cache.count(light_name) > 0;
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

void LightResource::destroy_scenelight(const std::string& light_name) {
	if (!is_scenelight_loaded(light_name)) {
		FatalError::fatal_error("Unable to locate and destroy scene light: " + light_name);
	}
	Print::print("Destroying Scene Light: " + light_name);
	m_scenelight_cache.erase(light_name);
}

void LightResource::destroy_all(){
	Print::print("Destroying LightResource");
	m_dirlight_cache.clear();
	m_pointlight_cache.clear();
	m_scenelight_cache.clear();
}
