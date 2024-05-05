#ifndef TEXTURE_H
#define TEXTURE_H

#define NumVerticesSquare 4

#include </usr/local/include/glm/gtx/transform.hpp>
#include </usr/include/GL/glew.h>

class Texture {
    public:
        Texture(glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f}, 
                glm::vec3 sideA = glm::vec3{1.0f, 0.0f, 0.0f}, 
                glm::vec3 sideB = glm::vec3{0.0f, 1.0f, 0.0f}, 
                glm::vec4 color1 = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f},
                glm::vec4 color2 = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
        ~Texture();

        void draw();

    private:
        GLuint vao;
        GLuint vbo;
        GLuint tex;
        GLfloat tex_data[4*4];
        glm::vec4 color1;
        glm::vec4 color2;
        GLfloat vertices[NumVerticesSquare][3 + 3 + 3] = { { 0.0f } };
};

#endif