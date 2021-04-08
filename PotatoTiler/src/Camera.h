#pragma once

#include <glm/glm.hpp>

class Camera
{
private:
	glm::vec3 m_Pos, m_Front, m_Up, m_Right, m_WorldUp;
	float m_Pitch, m_Yaw;
	float m_MovementSpeed;
public:
	Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch, float movementSpeed);
	~Camera();

	glm::mat4 getViewMatrix() const;
	void handleInputs(bool* keys, float xChange, float yChange, float delta);
};