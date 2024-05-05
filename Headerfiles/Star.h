#ifndef STAR_H
#define STAR_H

#define NumVerticesStar 66

#include </usr/local/include/glm/gtx/transform.hpp>
#include </usr/include/GL/glew.h>

class Star {
    public:
        Star(glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f}, 
               glm::vec3 top = glm::vec3{0.0f, 0.0f, 1.0f},
               glm::vec3 radius = glm::vec3{1.0f, 0.0f, 0.0f},
               glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 0.0f});
        ~Star();

        void draw();
        void setPosition(glm::vec3 position);

    private:
        void calculateVertices();

        GLuint vao;
        GLuint vbo;
        glm::vec3 position;
        glm::vec3 top;
        glm::vec3 radius;
        glm::vec4 color;
        GLfloat vertices[NumVerticesStar][3 + 4 + 3] = { { 0.0f } };
};

#endif