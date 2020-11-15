#pragma once
#include <glm/glm.hpp>

class MatrixFunctions{

public:
	
	// Normal matrix when working in world space in the shaders
	static glm::mat3 get_normal_matrix(const glm::mat4& model_matrix);

	// Normal matrix when working in view space in the shaders
	static  glm::mat3 get_normal_matrix(const glm::mat4& model_matrix, const glm::mat4& view_matrix);

	// Returns an objects world coordinates from a model_matrix transformation
	static glm::vec3 get_world_coordinates(glm::mat4& model_matrix);
	
};

// Normal Vectors
	// Normal vectors are perpendicular to the objects surface.  This is a more
	// generic 'per-surface' perpendicular vector

// Normal Matrix
	// The normal matrix is the transpose of the inverse of the upper-left
	// 3x3 model matrix.  This is normally calculated by the model-view matrix.
	// However, if we are working in world-space in our shaders (instead of
	// view space), we only need to use the model matrix.

	// The normal matrix keeps normal vectors in their proper angled position
	// even if an object is scaled.

// Normal Map (aka bump map)
	// A normal map creates a 'per-fragment' perpendicular vector.  This gives
	// a much higher level of detail as the light can act differently per
	// fragment
	//
	//  This is done by sampling from a 'normal map' (in the fragment shader).
	//  Normal vectors within normal maps are typically in tangent space.  To
	//  get lighting to work properly, we need to convert all lighting
	//  related vectors (e.g. light position, direction, etc.) into the same
	//  tangent space.  This is done via the inverse of the TBN (Tangent,
	//  BitTangent, Normal) matrix.  It is more efficient to convert the
	//  lighting variables into tangent space, because this is done in the
	//  vertex shader.  You could use another approach, and transform the
	//  tangent space normals (from the texture normal map sample) into world
	//  space (via the standard TBN matrix), but this is costly due to how much
	//  the fragment shader must run.
	//
	//  The TBN matrix is constructed from the normal vectors, tangent vectors,
	//  and bittangent vectors.  These are calculated during the model load
	//  (if they are not already created).
	//
	//  Tangent space is the space local per triangle.  The normals are relative
	//  to the local reference frame of the individual triangle