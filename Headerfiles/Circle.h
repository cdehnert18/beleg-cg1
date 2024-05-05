#ifndef CIRCLE_H
#define CIRCLE_H

#define NumVerticesCircle 33

#include </usr/local/include/glm/gtx/transform.hpp>
#include </usr/include/GL/glew.h>

class Circle {
    public:
        Circle(glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f}, 
               glm::vec3 front = glm::vec3{0.0f, 0.0f, 1.0f},
               glm::vec3 radius = glm::vec3{1.0f, 0.0f, 0.0f},
               glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 0.0f});
        ~Circle();

        void draw();

    private:
        GLuint vao;
        GLuint vbo;
        glm::vec4 color;
        GLfloat vertices[NumVerticesCircle][3 + 4 + 3] = { { 0.0f } };
};

#endif