#ifndef RECTANGLE_H
#define RECTANGLE_H

#define NumVerticesSquare 4

#include </usr/local/include/glm/gtx/transform.hpp>
#include </usr/include/GL/glew.h>

class Rectangle {
    public:
        Rectangle(glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f}, 
                glm::vec3 sideA = glm::vec3{1.0f, 0.0f, 0.0f}, 
                glm::vec3 sideB = glm::vec3{0.0f, 1.0f, 0.0f}, 
                glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
        ~Rectangle();

        void draw();

    private:
        GLuint vao;
        GLuint vbo;
        glm::vec4 color;
        GLfloat vertices[NumVerticesSquare][3 + 4 + 3] = { { 0.0f } };
};

#endif