#ifndef GESCHENK_H
#define GESCHENK_H

#include <memory>
#include </usr/local/include/glm/gtx/transform.hpp>
#include </usr/include/GL/glew.h>
#include "../Headerfiles/Texture.h"

class Geschenk {
    public:
        Geschenk(glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f}, 
               glm::vec3 sideA = glm::vec3{1.0f, 0.0f, 0.0f}, 
               glm::vec3 sideB = glm::vec3{0.0f, 1.0f, 0.0f}, 
               glm::vec3 sideC = glm::vec3{0.0f, 0.0f, 1.0f}, 
               glm::vec4 color1 = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f},
               glm::vec4 color2 = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
        ~Geschenk();

        void draw();

    private:
        glm::vec3 position;
        Texture* d;
        Texture* f;
        Texture* b;
        Texture* l;
        Texture* r;
        Texture* t;
};

#endif