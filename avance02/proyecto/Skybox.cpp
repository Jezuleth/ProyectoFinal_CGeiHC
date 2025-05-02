/*#include "Skybox.h"



Skybox::Skybox()
{
}

Skybox::Skybox(std::vector<std::string> faceLocations)
{
	skyShader = new Shader();
	skyShader->CreateFromFiles("shaders/skybox.vert", "shaders/skybox.frag");
	uniformProjection = skyShader->GetProjectionLocation();
	uniformView = skyShader->GetViewLocation();

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	int width, height, bitDepth;
	for (size_t i = 0; i < 6; i++)
	{

		unsigned char *texData = stbi_load(faceLocations[i].c_str(), &width, &height, &bitDepth, 0); //el tipo unsigned char es para un array de bytes de la imagen, obtener datos de la imagen 
		if (!texData)
		{
			printf("No se encontró : %s", faceLocations[i].c_str());
			return;
		}
		//para cambiar el origen a la esquina inferior izquierda como necesitamos
		//stbi_set_flip_vertically_on_load(true);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X +i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData); //SIN CANAL ALPHA A ENOS QUE QUERAMOS AGREGAR EFECTO DE PARALLAX
		stbi_image_free(texData); //para liberar la información de la imagen
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Creando el Mesh del skybox
	unsigned int skyboxIndices[] = {
		// front
		0, 1, 2,
		2, 1, 3,
		// right
		2, 3, 5,
		5, 3, 7,
		// back
		5, 7, 4,
		4, 7, 6,
		// left
		4, 6, 0,
		0, 6, 1,
		// top
		4, 0, 5,
		5, 0, 2,
		// bottom
		1, 6, 3,
		3, 6, 7
	};

	float skyboxVertices[] = {
		-1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,//v0
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,//V1
		1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,//V2
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,//V3
		-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,//V4
		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,//V5
		-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,//V6
		1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f//V7
	};
	skyMesh = new Mesh();
	skyMesh->CreateMesh(skyboxVertices, skyboxIndices, 64, 36);

}

void Skybox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	viewMatrix = glm::mat4(glm::mat3(viewMatrix));

	glDepthMask(false);
	skyShader->UseShader();
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	//skyShader->Validate();
	skyMesh->RenderMesh();
	glDepthMask(true);

}


Skybox::~Skybox()
{
}
*/

#include "Skybox.h"
#include "stb_image.h"
#include <iostream>

Skybox::Skybox() {}

Skybox::Skybox(std::vector<std::string> dayFaces, std::vector<std::string> nightFaces)
{
	skyShader = new Shader();
	skyShader->CreateFromFiles("shaders/skybox.vert", "shaders/skybox.frag");
	uniformProjection = skyShader->GetProjectionLocation();
	uniformView = skyShader->GetViewLocation();

	loadCubemap(dayFaces, textureIds[0]);
	loadCubemap(nightFaces, textureIds[1]);

	// Creación del mesh (igual que antes)
	unsigned int skyboxIndices[] = {
		0, 1, 2, 2, 1, 3,  2, 3, 5, 5, 3, 7,
		5, 7, 4, 4, 7, 6,  4, 6, 0, 0, 6, 1,
		4, 0, 5, 5, 0, 2,  1, 6, 3, 3, 6, 7
	};

	float skyboxVertices[] = {
		-1.0f, 1.0f, -1.0f,   0,0, 0,0,0,
		-1.0f, -1.0f, -1.0f,  0,0, 0,0,0,
		 1.0f, 1.0f, -1.0f,   0,0, 0,0,0,
		 1.0f, -1.0f, -1.0f,  0,0, 0,0,0,
		-1.0f, 1.0f, 1.0f,    0,0, 0,0,0,
		 1.0f, 1.0f, 1.0f,    0,0, 0,0,0,
		-1.0f, -1.0f, 1.0f,   0,0, 0,0,0,
		 1.0f, -1.0f, 1.0f,   0,0, 0,0,0
	};

	skyMesh = new Mesh();
	skyMesh->CreateMesh(skyboxVertices, skyboxIndices, sizeof(skyboxVertices), sizeof(skyboxIndices));
}

void Skybox::loadCubemap(std::vector<std::string> faces, GLuint& textureID)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, bitDepth;
	for (unsigned int i = 0; i < 6; i++)
	{
		unsigned char* texData = stbi_load(faces[i].c_str(), &width, &height, &bitDepth, 0);
		if (!texData)
		{
			std::cerr << "Fallo al cargar: " << faces[i] << std::endl;
			continue;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
			width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		stbi_image_free(texData);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Skybox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, float blendFactor)
{
	viewMatrix = glm::mat4(glm::mat3(viewMatrix)); // remove translation

	glDepthMask(GL_FALSE);
	skyShader->UseShader();

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glUniform1f(glGetUniformLocation(skyShader->GetShaderID(), "blendFactor"), blendFactor);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureIds[0]); // Día
	glUniform1i(glGetUniformLocation(skyShader->GetShaderID(), "dayCubemap"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureIds[1]); // Noche
	glUniform1i(glGetUniformLocation(skyShader->GetShaderID(), "nightCubemap"), 1);

	skyMesh->RenderMesh();
	glDepthMask(GL_TRUE);
}

Skybox::~Skybox() {}
