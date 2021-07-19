#include "MatrixFunctions.h"

// glm::mat3 MatrixFunctions::get_normal_matrix(const glm::mat4& model_matrix){
// 	return glm::mat3(glm::transpose(glm::inverse(model_matrix)));	
// }

glm::mat3 MatrixFunctions::get_normal_matrix(const glm::mat4& model_matrix, const glm::mat4& view_matrix) {
	return glm::mat3(glm::transpose(glm::inverse(view_matrix * model_matrix)));
}

glm::vec3 MatrixFunctions::get_world_coordinates(glm::mat4& model_matrix) {
	return glm::vec3(model_matrix[3][0], model_matrix[3][1], model_matrix[3][2]);
}