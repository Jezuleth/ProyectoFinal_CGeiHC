#include "Crash.h"

Crash::Crash()
{
    position = glm::vec3(0.004f, 2.617f, -4.616f);
    scale = glm::vec3(0.3f);
    moveSpeed = 0.3f;
    front = glm::vec3(0.0f, 0.0f, 1.0f);  // El frente inicial está mirando hacia el eje Z positivo
    right = glm::vec3(-1.0f, 0.0f, 0.0f);  // La derecha inicial está hacia el eje X negativo
    up = glm::vec3(0.0f, 1.0f, 0.0f);     // Arriba está hacia el eje Y positivo
    yaw = 90.0f;  // Yaw inicial para mirar hacia el frente
    turnSpeed = 10.0f;  // Velocidad de rotación

    walkTimer = 0.5f;
    walkSpeed = 0.4f;
    walkAmplitude = 40.0f;

    armTimer = 0.5f;
    armSpeed = 0.4f;
    armAmplitude = 20.f;

}

void Crash::init()
{
    cuerpo.LoadModel("Models/crash_cuerpo.obj");
    piernaIzq.LoadModel("Models/crash_pierna_izquierda.obj");
    piernaDer.LoadModel("Models/crash_pierna_derecha.obj");
    pieIzq.LoadModel("Models/crash_pie_izquierdo.obj");
    pieDer.LoadModel("Models/crash_pie_derecho.obj");
    brazoDer.LoadModel("Models/crash_brazo_derecho.obj");
    brazoIzq.LoadModel("Models/crash_brazo_izquierdo.obj");
}

void Crash::update(bool* keys, GLfloat deltaTime)
{
    // 1. Movimiento y rotación (antes keyControl)
    GLfloat velocity = moveSpeed * deltaTime;
    if (keys[GLFW_KEY_W]) position += front * velocity;
    if (keys[GLFW_KEY_S]) position -= front * velocity;
    if (keys[GLFW_KEY_A]) position -= right * velocity;
    if (keys[GLFW_KEY_D]) position += right * velocity;
    if (keys[GLFW_KEY_Q]) yaw -= turnSpeed * deltaTime;
    if (keys[GLFW_KEY_E]) yaw += turnSpeed * deltaTime;

    // 2. Actualizar orientación
    front.x = cos(glm::radians(yaw));
    front.z = sin(glm::radians(yaw));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
    up = glm::normalize(glm::cross(right, front));

    // 3. Animación de caminar
    bool isWalking = keys[GLFW_KEY_W] || keys[GLFW_KEY_S];
    if (isWalking) {
        walkTimer += deltaTime;
        armTimer += deltaTime;
    }
    else {
        walkTimer = 0.0f;
        armTimer = 0.0f;
    }

}

void Crash::setPosition(glm::vec3 newPosition)
{
    position = newPosition;
}

void Crash::setScale(glm::vec3 newScale) {
    scale = newScale;
}


glm::vec3 Crash::getPosition() const {
    return position;
}

glm::vec3 Crash::getFront() const {
    return front;
}

float Crash::getYaw() const {
    return yaw;
}

void Crash::drawLimb(GLuint uniformModel,
    const glm::mat4& parentTransform,
    const glm::vec3& offsetParent,
    float             angleDeg,
    const glm::vec3& rotAxis,
    const glm::vec3& offsetChild,
    Model& parentModel,
    Model* childModel) {
    // Paso 1: trasladar al offset de la parte principal
    glm::mat4 m = glm::translate(parentTransform, offsetParent);
    // Paso 2: rotar según el ángulo
    m = glm::rotate(m, glm::radians(angleDeg), rotAxis);
    // Dibujamos la parte principal
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(m));
    parentModel.RenderModel();

    // Si hay una parte hija, la dibujamos tras desplazarla de la parte padre
    if (childModel) {
        glm::mat4 childM = glm::translate(m, offsetChild);
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(childM));
        childModel->RenderModel();
    }
}


void Crash::render(GLuint uniformModel) {
    // 1) Cálculos de ángulo
    float legAngle = sin(walkTimer * walkSpeed) * walkAmplitude;
    float armAngle = sin(armTimer * armSpeed) * armAmplitude;


    // 2) Transformación base: posición, escala y rotación global
    glm::mat4 base = glm::mat4(1.0f);
    base = glm::translate(base, position);
    base = glm::rotate(base, glm::radians(yaw - 90.0f), glm::vec3(0, -1, 0));
    base = glm::scale(base, scale);

    // 3) Dibujar cuerpo
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(base));
    cuerpo.RenderModel();

    // 4) Pierna derecha + pie
    drawLimb(uniformModel,
        base,
        glm::vec3(0.004f, -5.47f, -2.208f),  // offset pierna
        legAngle,                            // ángulo pierna
        glm::vec3(1, 0, 0),                    // rotar en X
        glm::vec3(-1.588f, -4.338f, -0.176f),// offset pie
        piernaDer,
        &pieDer);

    // 5) Pierna izquierda + pie (fase opuesta)
    drawLimb(uniformModel,
        base,
        glm::vec3(-0.004f, -5.47f, -2.208f),
        -legAngle,
        glm::vec3(1, 0, 0),
        glm::vec3(1.588f, -4.338f, -0.176f),
        piernaIzq,
        &pieIzq);

    // 6) Brazos
    // Brazo derecho, fase opuesta a pierna derecha
    drawLimb(uniformModel,
        base,
        glm::vec3(-1.897f, 0.087f, -2.069f),  // offset brazo der
        -armAngle,                            // rotación en X
        glm::vec3(1, 0, 0),
        glm::vec3(0),                         // sin hijo
        brazoDer);

    // Brazo izquierdo, misma fase que pierna derecha
    drawLimb(uniformModel,
        base,
        glm::vec3(1.897f, 0.087f, -2.069f),  // offset brazo izq
        +armAngle,
        glm::vec3(1, 0, 0),
        glm::vec3(0),
        brazoIzq);
}
