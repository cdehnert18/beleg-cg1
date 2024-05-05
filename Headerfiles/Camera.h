#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include </usr/local/include/glm/gtc/matrix_transform.hpp>

class Camera {
public:
    //Konstruktor mit Default-Werten
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
           glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float fov = 50.0f, float aspectRatio = 1.0f, float nearClip = 0.01f, float farClip = 100.0f);

    /*Setter*/
    void setPosition(glm::vec3 position);
    void setTarget(glm::vec3 target);
    void setAspectRatio(float aspectRatio);

    /*Getter*/
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    /*View - Matrix */
    glm::mat4 viewMatrix;
    //Kameraposition im Raum(x, y, z)
    glm::vec3 position;
    //Anvisierter Punkt im Raum(x, y, z)
    glm::vec3 target;
    //Deklaration, wo "oben" ist 
    glm::vec3 up;

    /*Projektionsmatrix*/
    glm::mat4 projectionMatrix;
    //Sichtfeld
    float fov;
    //Seitenverh�ltnis
    float aspectRatio;
    //Minimale Entfernung
    float nearClip;
    //maximale Entfernung
    float farClip;

private:
    void updateViewMatrix();
    void updateProjectionMatrix();
};

#endif
