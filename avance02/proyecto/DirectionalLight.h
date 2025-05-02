#pragma once
#include "Light.h"

class DirectionalLight :
	public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
					GLfloat aIntensity, GLfloat dIntensity,
					GLfloat xDir, GLfloat yDir, GLfloat zDir);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientcolorLocation,
		GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	void setDirection(GLfloat x, GLfloat y, GLfloat z);
	void setColor(GLfloat r, GLfloat g, GLfloat b);
	void setAmbientIntensity(GLfloat intensity);
	void setDiffuseIntensity(GLfloat intensity);

	~DirectionalLight();

private:
	glm::vec3 direction;
};

