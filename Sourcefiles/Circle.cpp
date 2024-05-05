#include "../Headerfiles/Circle.h"
#include "../Headerfiles/GLManager.h"
#include "iostream"
#include </usr/include/GL/glew.h>

Circle::Circle(glm::vec3 position, glm::vec3 front, glm::vec3 radius, glm::vec4 color) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    this->color = color;
   
    GLfloat PI = 3.14;
    vertices[0][0] = position.x;
	vertices[0][1] = position.y;
    vertices[0][2] = position.z;
    
    glm::vec3 n1 = glm::normalize(radius);
    glm::vec3 n2 = glm::normalize(cross(radius, front));
	
    for (int i = 1; i < NumVerticesCircle; i++) {
        vertices[i][0] = position.x + radius.x * cos(2 * PI * i / 30) * n1.x + radius.x * sin(2 * PI * i / 30) * n2.x;
        vertices[i][1] = position.y + radius.x * cos(2 * PI * i / 30) * n1.y + radius.x * sin(2 * PI * i / 30) * n2.y;
        vertices[i][2] = position.z + radius.x * cos(2 * PI * i / 30) * n1.z + radius.x * sin(2 * PI * i / 30) * n2.z;
    }
    
    for (int i = 0; i < NumVerticesCircle; i++) {
        vertices[i][3] = color.r;
        vertices[i][4] = color.g;
        vertices[i][5] = color.b;
        vertices[i][6] = color.a;
    }

    glm::vec3 normal = glm::normalize(front);
    for (int i = 0; i < NumVerticesCircle; i++) {
        vertices[i][7] = normal.x;
        vertices[i][8] = normal.y;
        vertices[i][9] = normal.z;
    }

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

Circle::~Circle() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Circle::draw() {
    glBindVertexArray(vao);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLE_FAN, 0, NumVerticesCircle);
}
