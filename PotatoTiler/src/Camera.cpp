#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch, float movementSpeed)
	:m_Pos(pos), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch), m_MovementSpeed(movementSpeed)
{
	m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front.y = sin(glm::radians(m_Pitch));
	m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);
}

void Camera::handleInputs(bool* keys, float xChange, float yChange, float delta)
{
	if (keys[GLFW_MOUSE_BUTTON_2])
	{
		xChange *= m_MovementSpeed * delta;
		yChange *= m_MovementSpeed * delta;

		m_Pos += m_Right * xChange;
		m_Pos += m_Up * yChange;
	}
}