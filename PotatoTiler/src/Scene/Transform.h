#pragma once

#include <glm/glm.hpp>

struct Transformation
{
	glm::vec2 translation;
	float rotation;
	glm::vec2 scale;

	Transformation();
	Transformation(glm::vec2 translation, float rotation, glm::vec2 scaling);
	glm::mat4 getModelMat() const;
};