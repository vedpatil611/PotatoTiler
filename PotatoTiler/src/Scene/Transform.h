#pragma once

#include <glm/glm.hpp>

struct Transformation
{
	glm::vec3 translation;
	float rotation;
	glm::vec3 scale;

	Transformation();
	Transformation(glm::vec3 translation, float rotation, glm::vec3 scaling);
	glm::mat4 getModelMat() const;
};