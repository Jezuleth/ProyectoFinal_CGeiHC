#include "Camera.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_I])
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_K])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_J])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_L])
	{
		position += right * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}


glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::setPosition(glm::vec3 newPosition ,GLfloat newYaw, GLfloat newPitch)
{
	position = newPosition;
	pitch = newPitch;
	yaw = newYaw;
	update();
}
/*
void Camera::followPlayer(glm::vec3 newPosition, GLfloat newYaw, glm::vec3 newFront)
{
	front = newFront;
	position = newPosition;
	pitch = -20.0f;
	yaw = newYaw;
	update();
}
*/

void Camera::followPlayer(const glm::vec3& targetPos,
	float distance,
	float heightOffset,
	float yawDeg,
	float pitchDeg)
{
	// 1) Cálculo del offset esférico
	float yaw = glm::radians(yawDeg);
	float pitch = glm::radians(pitchDeg);

	float x = distance * cos(pitch) * cos(yaw);
	float y = distance * sin(pitch) + heightOffset;
	float z = distance * cos(pitch) * sin(yaw);

	glm::vec3 offset = glm::vec3(x, y, z);

	// 2) Posicionar la cámara detrás del jugador
	position = targetPos - offset;

	// 3) Apuntar al jugador
	front = glm::normalize(targetPos - position);

	// 4) Ajuste opcional de pitch/yaw internos
	this->yaw = yawDeg;
	this->pitch = pitchDeg;

	// 5) Actualizar matrices
	update();
}


Camera::~Camera()
{
}
