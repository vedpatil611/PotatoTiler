#include "Transform.h"

#include "glm/gtc/matrix_transform.hpp"

Transformation::Transformation()
	:translation(0.0f, 0.0f), rotation(0), scale(1.0f, 1.0f)
{}

Transformation::Transformation(glm::vec2 translation, float rotation, glm::vec2 scaling)
	:translation(translation), rotation(rotation), scale(scaling)
{}

glm::mat4 Transformation::getModelMat() const
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(translation, 0.0f));
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(scale, 1.0f));
	return model;
}
