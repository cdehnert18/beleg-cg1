#include "../Headerfiles/Texture.h"
#include "../Headerfiles/GLManager.h"
#include "iostream"

Texture::Texture(glm::vec3 position, glm::vec3 sideA, glm::vec3 sideB, glm::vec4 color1, glm::vec4 color2) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    this->color1 = color1;
    this->color2 = color2;
   
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

    vertices[0][3] = 0.0;
    vertices[0][4] = 0.0;

    vertices[1][3] = 0;
    vertices[1][4] = 1;

    vertices[2][3] = 1;
    vertices[2][4] = 1;

    vertices[3][3] = 1;
    vertices[3][4] = 0;

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    tex_data[0] = color2.r; tex_data[1] = color2.g; tex_data[2] = color2.b; tex_data[3] = color2.a;
    tex_data[4] = color1.r; tex_data[5] = color1.g; tex_data[6] = color1.b; tex_data[7] = color1.a;
    tex_data[8] = color1.r; tex_data[9] = color1.g; tex_data[10] = color1.b; tex_data[11] = color1.a;
    tex_data[12] = color2.r; tex_data[13] = color2.g; tex_data[14] = color2.b; tex_data[15] = color2.a;
    //Beispiel: static const GLfloat tex_data[] = {1,0,0,1, 0,1,0,1, 0,0,1,1, 1,1,0,1};
    
    glTexStorage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 2, 2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGBA, GL_FLOAT, tex_data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glm::vec3 normal = glm::cross(sideA, sideB);
    normal = glm::normalize(normal);
    for (int i = 0; i < NumVerticesSquare; i++) {
        vertices[i][5] = normal.x;
        vertices[i][6] = normal.y;
        vertices[i][7] = normal.z;
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   
     // Positionen
    glVertexAttribPointer(GLManager::vPosition, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(GLManager::vPosition);

    // Farben
    glVertexAttribPointer(GLManager::vTexture, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(GLManager::vTexture);

    // Normalen
    glVertexAttribPointer(GLManager::vNormal, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(GLManager::vNormal);
}

Texture::~Texture() {
    glDeleteBuffers(1, &vbo);   // Lösche den Vertex-Buffer
    glDeleteVertexArrays(1, &vao); // Lösche das Vertex-Array
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::draw() {
    glBindVertexArray(vao);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLE_FAN, 0, NumVerticesSquare);
    glBindTexture(tex, 0);
}
