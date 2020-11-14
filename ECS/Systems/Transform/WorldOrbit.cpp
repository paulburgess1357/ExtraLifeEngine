#include "WorldOrbit.h"
#include "../../Components/Transform/TransformComponent.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Transform::WorldOrbit::update(entt::registry& registry){	
	registry.view<TransformComponent, OrbitComponent>().each([](auto& transform, auto& orbit_component) {
		glm::mat4 orbit_matrix = orbit(orbit_component);
		transform.m_model_matrix = orbit_matrix * transform.m_model_matrix;
	});
}

glm::mat4 Transform::WorldOrbit::orbit(OrbitComponent& orbit){
	
	// Orbits the current object from its current position around the objects
	// center.  The center is the value used in the transform component world
	// position

	orbit.m_current_orbit += orbit.m_orbit_offset;
	clamp_orbit_orientation(orbit.m_current_orbit);

	// Scale movement vector
	// This vector is how far along each axis you want to move (from origin).
	// The resulting distance from the origin will be used as the distance to
	// rotate the object
	orbit.m_movement_from_center_axis = orbit.m_movement_from_center_axis / (orbit.m_movement_from_center_axis.x + orbit.m_movement_from_center_axis.y + orbit.m_movement_from_center_axis.z) * orbit.m_radius;

	// Additional rotation can be applied here.  If you would like to prevent
	// the object from rotating as it orbits the center, you can rotate the
	// object in the opposite direction and use the same rotation axis.
	glm::mat4 rotation_matrix(1);
	if (orbit.m_maintain_orientation) {
		rotation_matrix = glm::mat4_cast(apply_counter_rotation(orbit));
	}

	// Orbiting is relative to the origin.  The rotation around the origin is
	// applied.  The object is then moved to where the orbit center is located.
	const glm::mat4 movement_from_origin = glm::translate(glm::mat4(1.0f), orbit.m_movement_from_center_axis);
	const glm::mat4 rotation_around_origin = glm::rotate(glm::mat4(1.0f), glm::radians(orbit.m_current_orbit), glm::normalize(orbit.m_custom_orbit_axis));

	return rotation_around_origin * movement_from_origin * rotation_matrix;
}

glm::quat Transform::WorldOrbit::apply_counter_rotation(OrbitComponent& orbit){

	// User defined axis (normalized)
	orbit.m_maintain_orientation_rotation_tracker -= orbit.m_orbit_offset;
	clamp_orbit_orientation(orbit.m_maintain_orientation_rotation_tracker);

	// Calculate rotation around the user defined rotation axis	
	return glm::angleAxis(glm::radians(orbit.m_maintain_orientation_rotation_tracker), glm::normalize(orbit.m_custom_orbit_axis));
	
}

void Transform::WorldOrbit::clamp_orbit_orientation(float& orientation_value){
	if (orientation_value >= 360.0f) {
		orientation_value = 0.0f;
	}

	if (orientation_value <= -360.0f) {
		orientation_value = 0.0f;
	}
}
