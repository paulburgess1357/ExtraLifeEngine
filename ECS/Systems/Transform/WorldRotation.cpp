#include "WorldRotation.h"
#include "../../Components/Transform/TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>

const glm::vec3 Transform::WorldRotation::DEFAULT_ROTATION_X{ 1, 0, 0 };
const glm::vec3 Transform::WorldRotation::DEFAULT_ROTATION_Y{ 0, 1, 0 };
const glm::vec3 Transform::WorldRotation::DEFAULT_ROTATION_Z{ 0, 0, 1 };

void Transform::WorldRotation::update(entt::registry& registry){	
	registry.view<TransformComponent, RotationComponent>().each([](auto& transform, auto& rotation) {
		const glm::mat4 rotation_matrix = glm::mat4_cast(pitch(rotation) * yaw(rotation) * roll(rotation) * rotate_custom_axis(rotation));
		transform.m_model_matrix *= rotation_matrix;
	});
}

glm::quat Transform::WorldRotation::pitch(RotationComponent& rotation) {	
	rotation.m_current_pitch += rotation.m_pitch_offset;
	clamp_rotation_orientation(rotation.m_current_pitch);
	
	// Calculate rotation around the default x axis (likely same as world axis)	
	return glm::angleAxis(glm::radians(rotation.m_current_pitch), DEFAULT_ROTATION_X);
}

glm::quat Transform::WorldRotation::yaw(RotationComponent& rotation) {
	rotation.m_current_yaw += rotation.m_yaw_offset;
	clamp_rotation_orientation(rotation.m_current_yaw);
	
	// Calculate rotation around the default y axis (likely same as world axis)
	return glm::angleAxis(glm::radians(-rotation.m_current_yaw), DEFAULT_ROTATION_Y);
}

glm::quat Transform::WorldRotation::roll(RotationComponent& rotation) {
	rotation.m_current_roll += rotation.m_roll_offset;
	clamp_rotation_orientation(rotation.m_current_roll);

	// Calculate rotation around the default z axis (likely same as world axis)
	return glm::angleAxis(glm::radians(rotation.m_current_roll), DEFAULT_ROTATION_Z);
}

glm::quat Transform::WorldRotation::rotate_custom_axis(RotationComponent& rotation) {

	// User defined axis (normalized)
	rotation.m_current_custom_rotation += rotation.m_rotation_offset;
	clamp_rotation_orientation(rotation.m_current_custom_rotation);

	// Calculate rotation around the user defined rotation axis	
	return glm::angleAxis(glm::radians(rotation.m_current_custom_rotation), glm::normalize(rotation.m_custom_rotation_axis));
}

void Transform::WorldRotation::clamp_rotation_orientation(float& orientation_value){
	if (orientation_value >= 360.0f) {
		orientation_value = 0.0f;
	}

	if (orientation_value <= -360.0f) {
		orientation_value = 0.0f;
	}
}
