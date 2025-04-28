#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
									GLfloat aIntensity, GLfloat dIntensity,
									GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(red, green, blue, aIntensity, dIntensity)
{
	direction = glm::vec3(xDir, yDir, zDir);
}

void DirectionalLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientcolorLocation,
	GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{
	glUniform3f(ambientcolorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

void DirectionalLight::setDirection(GLfloat x, GLfloat y, GLfloat z) {
	direction = glm::vec3(x, y, z);
}

void DirectionalLight::setColor(GLfloat r, GLfloat g, GLfloat b) {
	color = glm::vec3(r, g, b);
}

void DirectionalLight::setAmbientIntensity(GLfloat intensity) {
	ambientIntensity = intensity;
}

void DirectionalLight::setDiffuseIntensity(GLfloat intensity) {
	diffuseIntensity = intensity;
}



DirectionalLight::~DirectionalLight()
{
}
