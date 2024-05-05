#include "../Headerfiles/Cylinder.h"
#include "../Headerfiles/GLManager.h"
#include "iostream"
#include </usr/include/GL/glew.h>

Cylinder::Cylinder(glm::vec3 position, glm::vec3 top, glm::vec3 radius, glm::vec4 color) {

    this->color = color;
    this->position = position;

    d = new Circle(position, {top.x * -1, top.y * -1, top.z * -1}, radius, color);
    t = new Circle(position + top, top, radius, color);

    GLfloat PI = 3.14;  
    GLfloat x1;
    GLfloat y1;
    GLfloat z1;
    GLfloat x2;
    GLfloat y2;
    GLfloat z2;
    glm::vec3 n1 = glm::normalize(radius);
    glm::vec3 n2 = glm::normalize(cross(radius, top));

    for (int i = 1; i < NumVerticesCircle; i++) {
        x1 = position.x + radius.x * cos(2 * PI * i / 30) * n1.x + radius.x * sin(2 * PI * i / 30) * n2.x;
        y1 = position.y + radius.x * cos(2 * PI * i / 30) * n1.y + radius.x * sin(2 * PI * i / 30) * n2.y;
        z1 = position.z + radius.x * cos(2 * PI * i / 30) * n1.z + radius.x * sin(2 * PI * i / 30) * n2.z;

        x2 = position.x + radius.x * cos(2 * PI * (i+1) / 30) * n1.x + radius.x * sin(2 * PI * (i+1) / 30) * n2.x;
        y2 = position.y + radius.x * cos(2 * PI * (i+1) / 30) * n1.y + radius.x * sin(2 * PI * (i+1) / 30) * n2.y;
        z2 = position.z + radius.x * cos(2 * PI * (i+1) / 30) * n1.z + radius.x * sin(2 * PI * (i+1) / 30) * n2.z;

        glm::vec3 pos1 = {x1+x2, y1+y2, z1+z2};
        glm::vec3 pos = {pos1.x/2, pos1.y/2, pos1.z/2};
        glm::vec3 m = {pos.x +(top.x/2), pos.y+(top.y/2), pos.z+(top.z/2)};
        glm::vec3 sideB = {x2-x1, 0, z2-z1};
        glm::vec3 sideA = {0, top.y, 0};
        pList.addToList(new Rectangle(m, sideA, sideB, color));
    }

}

Cylinder::~Cylinder() {
    delete d;
    delete t;
    while(pList.getSize() != 0){
        pList.removeFromList(0);
    }
}

void Cylinder::draw() {
    d->draw();
    t->draw();
    for(int i = 0; i < pList.getSize(); i++){
        pList.getFromList(i)->draw();
    }
}
