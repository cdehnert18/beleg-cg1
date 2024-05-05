#include "../Headerfiles/Star.h"
#include "../Headerfiles/GLManager.h"
#include </usr/include/GL/glew.h>
#include "iostream"

Star::Star(glm::vec3 position, glm::vec3 top, glm::vec3 radius, glm::vec4 color) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    this->position = position;
    this->top = top;
    this->radius = radius;
    this->color = color;
   
    calculateVertices();

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   
     // Positionen
    glVertexAttribPointer(GLManager::vPosition, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(GLManager::vPosition);

    // Farben
    glVertexAttribPointer(GLManager::vColor, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(GLManager::vColor);

    // Normalen
    glVertexAttribPointer(GLManager::vNormal, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));
    glEnableVertexAttribArray(GLManager::vNormal);
}

Star::~Star() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Star::draw() {
    glBindVertexArray(vao);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLE_FAN, 0, NumVerticesStar);
}

void Star::setPosition(glm::vec3 position) {
    this->position = position;
    calculateVertices();
}

void Star::calculateVertices(){
    GLfloat PI = 3.14;
    vertices[0][0] = position.x;
	vertices[0][1] = position.y;
    vertices[0][2] = position.z;
    vertices[0][7] = top.x;
    vertices[0][8] = top.y;
    vertices[0][9] = top.z;

    vertices[1][0] = position.x + top.x;
	vertices[1][1] = position.y + top.y;
    vertices[1][2] = position.z + top.z;
    vertices[0][7] = top.x * -1;
    vertices[0][8] = top.y * -1;
    vertices[0][9] = top.z * -1;

    glm::vec3 n1 = glm::normalize(radius);
    glm::vec3 n2 = glm::normalize(cross(radius, top));
    
	for (int i = 2; i < NumVerticesStar; i++) {
        if(i % 2 == 0){
            //vertices[i][0] = position.x + cos(2 * PI * i / 30) * radius.x + sin(2 * PI * i / 30) * cross(radius, top).x + top.x;
		    //vertices[i][1] = position.y + cos(2 * PI * i / 30) * radius.y + sin(2 * PI * i / 30) * cross(radius, top).y + top.y;
            //vertices[i][2] = position.z + cos(2 * PI * i / 30) * radius.z + sin(2 * PI * i / 30) * cross(radius, top).z + top.z;

            vertices[i][0] = position.x + radius.x * cos(2 * PI * i / 30) * n1.x + radius.x * sin(2 * PI * i / 30) * n2.x + top.x;
            vertices[i][1] = position.y + radius.x * cos(2 * PI * i / 30) * n1.y + radius.x * sin(2 * PI * i / 30) * n2.y + top.y;
            vertices[i][2] = position.z + radius.x * cos(2 * PI * i / 30) * n1.z + radius.x * sin(2 * PI * i / 30) * n2.z + top.z;
        }else{
            //vertices[i][0] = position.x + cos(2 * PI * i / 30) * radius.x + sin(2 * PI * i / 30) * cross(radius, top).x;
		    //vertices[i][1] = position.y + cos(2 * PI * i / 30) * radius.y + sin(2 * PI * i / 30) * cross(radius, top).y;
            //vertices[i][2] = position.z + cos(2 * PI * i / 30) * radius.z + sin(2 * PI * i / 30) * cross(radius, top).z;

            vertices[i][0] = position.x + radius.x * cos(2 * PI * i / 30) * n1.x + radius.x * sin(2 * PI * i / 30) * n2.x;
            vertices[i][1] = position.y + radius.x * cos(2 * PI * i / 30) * n1.y + radius.x * sin(2 * PI * i / 30) * n2.y;
            vertices[i][2] = position.z + radius.x * cos(2 * PI * i / 30) * n1.z + radius.x * sin(2 * PI * i / 30) * n2.z;
        }
        vertices[i][7] = vertices[i][0];
        vertices[i][8] = vertices[i][1];
        vertices[i][9] = vertices[i][2];
    }
    
    for (int i = 0; i < NumVerticesStar; i++) {
        vertices[i][3] = color.r;
        vertices[i][4] = color.g;
        vertices[i][5] = color.b;
        vertices[i][6] = color.a;
    }
}