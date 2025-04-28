#pragma once
#include "Model.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include<glfw3.h>
class Crash
{
public:
    Crash();
    void init();  // Cargar modelos
    void render(GLuint uniformModel); // Renderizar todo el personaje
    void setPosition(glm::vec3 newPosition);
    void setScale(glm::vec3 newScale);
    glm::vec3 getPosition() const;
    glm::vec3 getFront() const;
    float getYaw() const;
    void update(bool* keys, GLfloat deltaTime);


private:
    Model cuerpo, piernaIzq, piernaDer, pieIzq, pieDer, brazoIzq, brazoDer;
    glm::vec3 position;
    glm::vec3 scale;
    float moveSpeed;
    glm::vec3 front;   // Dirección hacia donde mira el personaje
    glm::vec3 right;   // Dirección hacia la derecha
    glm::vec3 up;      // Dirección hacia arriba
    GLfloat yaw;  // Agregar el yaw (rotación en Y)
    GLfloat turnSpeed;  // Velocidad de rotación


    float walkTimer, walkSpeed, walkAmplitude;
    float armTimer, armSpeed, armAmplitude;

    // Método auxiliar para dibujar una rama padre→hijo
    void drawLimb(GLuint uniformModel,
        const glm::mat4& parentTransform,
        const glm::vec3& offsetParent,
        float               angleDeg,
        const glm::vec3& rotAxis,
        const glm::vec3& offsetChild,
        Model& parentModel,
        Model* childModel = nullptr);
};

