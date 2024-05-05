#include "../Headerfiles/Rad.h"
#include "../Headerfiles/GLManager.h"
#include "iostream"
#include </usr/include/GL/glew.h>

Rad::Rad(glm::vec3 position, glm::vec4 color) {

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    GLfloat PI = 3.14;
    GLfloat radius = 2;
	vertices[0][0] = position.x;
	vertices[0][1] = position.y;
    vertices[0][2] = position.z;
	for (int i = 1; i < NumVerticesCircle; i++) {
		vertices[i][0] = radius * sin(2 * PI * i / 30) + position.x;
		vertices[i][1] = radius * cos(2 * PI * i / 30) + position.y;
        vertices[i][2] = position.z;
	}
	//vertices[1][0] = r * sin(2*PI*1/30);

    for (int i = 0; i < NumVerticesCircle; i++) {
        vertices[i][3] = color.r;
        vertices[i][4] = color.g;
        vertices[i][5] = color.b;
        vertices[i][6] = color.a;
    }

    glm::vec3 normal = {1, 1, 1};
    normal = glm::normalize(normal);
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

Rad::~Rad() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Rad::draw() {
    glBindVertexArray(vao);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLE_FAN, 0, NumVerticesCircle);
}
