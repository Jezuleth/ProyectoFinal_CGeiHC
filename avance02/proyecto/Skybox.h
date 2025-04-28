/*#pragma once

#include "CommonValues.h"
#include <vector>
#include <string>
#include<glew.h>
#include<glm.hpp>
#include<glfw3.h>
#include <gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include "Mesh.h"
#include "Shader_light.h"
class Skybox
{
public:
	Skybox();
	Skybox(std::vector<std::string> faceLocations);
	void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
		
	~Skybox();
private:
	Mesh* skyMesh;
	Shader* skyShader;
	GLuint textureId;
	GLuint uniformProjection, uniformView;

};
*/


#pragma once

#include "CommonValues.h"
#include <vector>
#include <string>
#include <glew.h>
#include <glm.hpp>
#include <glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Mesh.h"
#include "Shader_light.h"

class Skybox
{
public:
	Skybox();
	Skybox(std::vector<std::string> dayFaces, std::vector<std::string> nightFaces);
	void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, float blendFactor); // nuevo método con blending
	~Skybox();

private:
	void loadCubemap(std::vector<std::string> faces, GLuint& textureID); // helper para cargar texturas

	Mesh* skyMesh;
	Shader* skyShader;
	GLuint textureIds[2]; // 0 = día, 1 = noche
	GLuint uniformProjection, uniformView;
};