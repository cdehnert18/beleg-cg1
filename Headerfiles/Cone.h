#ifndef CONE_H
#define CONE_H

#define NumVerticesCone 33

#include </usr/local/include/glm/gtx/transform.hpp>
#include </usr/include/GL/glew.h>
#include "../Headerfiles/Circle.h"

class Cone {
    public:
        Cone(glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f}, 
               glm::vec3 top = glm::vec3{0.0f, 0.0f, 1.0f},
               glm::vec3 radius = glm::vec3{1.0f, 0.0f, 0.0f},
               glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 0.0f});
        ~Cone();

        void draw();

    private:
        Circle* d;
        GLuint vao;
        GLuint vbo;
        glm::vec4 color;
        GLfloat vertices[NumVerticesCone][3 + 4 + 3] = { { 0.0f } };
};

#endif