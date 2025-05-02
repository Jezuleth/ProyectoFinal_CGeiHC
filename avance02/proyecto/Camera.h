#pragma once

#include <glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <glfw3.h>

/*
enum class CameraMode {
	Free,
	FirstPerson,
	ThirdPerson,
	Aerial
};
*/

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();

	void setPosition(glm::vec3 newPositon, GLfloat newYaw, GLfloat newPitch);
	//void followPlayer(glm::vec3 newPositon, GLfloat newYaw, glm::vec3 newFront);
	void followPlayer(const glm::vec3& targetPos, float distance, float heightOffset, float yawDeg, float pitchDeg);
	//CameraMode getMode() const { return mode; }

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	// Para modos de cámara
	//CameraMode mode = CameraMode::Free;
	//glm::vec3 targetPosition;
	//float     targetYaw;

	void update();
};

