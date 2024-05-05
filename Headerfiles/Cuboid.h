#ifndef CUBOID_H
#define CUBOID_H

#include <memory>
#include </usr/local/include/glm/gtx/transform.hpp>
#include </usr/include/GL/glew.h>
#include "../Headerfiles/Rectangle.h"

class Cuboid {
    public:
        Cuboid(glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f}, 
               glm::vec3 sideA = glm::vec3{1.0f, 0.0f, 0.0f}, 
               glm::vec3 sideB = glm::vec3{0.0f, 1.0f, 0.0f}, 
               glm::vec3 sideC = glm::vec3{0.0f, 0.0f, 1.0f}, 
               glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
        ~Cuboid();

        void draw();

    private:
        glm::vec3 position;
        Rectangle* d;
        Rectangle* f;
        Rectangle* b;
        Rectangle* l;
        Rectangle* r;
        Rectangle* t;
};

#endif