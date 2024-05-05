#include "../Headerfiles/Rectangle.h"
#include "../Headerfiles/GLManager.h"
#include "iostream"

Rectangle::Rectangle(glm::vec3 position, glm::vec3 sideA, glm::vec3 sideB, glm::vec4 color) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    this->color = color;
   
    vertices[0][0] = position.x - 0.5 * sideA.x - 0.5 * sideB.x;
    vertices[0][1] = position.y - 0.5 * sideA.y - 0.5 * sideB.y;
    vertices[0][2] = position.z - 0.5 * sideA.z - 0.5 * sideB.z;

    vertices[1][0] = position.x + 0.5 * sideA.x - 0.5 * sideB.x;
    vertices[1][1] = position.y + 0.5 * sideA.y - 0.5 * sideB.y;
    vertices[1][2] = position.z + 0.5 * sideA.z - 0.5 * sideB.z;

    vertices[2][0] = position.x + 0.5 * sideA.x + 0.5 * sideB.x;
    vertices[2][1] = position.y + 0.5 * sideA.y + 0.5 * sideB.y;
    vertices[2][2] = position.z + 0.5 * sideA.z + 0.5 * sideB.z;

    vertices[3][0] = position.x - 0.5 * sideA.x + 0.5 * sideB.x;
    vertices[3][1] = position.y - 0.5 * sideA.y + 0.5 * sideB.y;
    vertices[3][2] = position.z - 0.5 * sideA.z + 0.5 * sideB.z;

    for (int i = 0; i < NumVerticesSquare; i++) {
        vertices[i][3] = color.r;
        vertices[i][4] = color.g;
        vertices[i][5] = color.b;
        vertices[i][6] = color.a;
    }

    glm::vec3 normal = glm::cross(sideA, sideB);
    normal = glm::normalize(normal);
    for (int i = 0; i < NumVerticesSquare; i++) {
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

Rectangle::~Rectangle() {
    glDeleteBuffers(1, &vbo);   // Lösche den Vertex-Buffer
    glDeleteVertexArrays(1, &vao); // Lösche das Vertex-Array
}

void Rectangle::draw() {
    glBindVertexArray(vao);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLE_FAN, 0, NumVerticesSquare);
}