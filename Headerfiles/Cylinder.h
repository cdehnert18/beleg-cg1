#ifndef CYLINDER_H
#define CYLINDER_H

#define NumVerticesCylinder 32

#include <memory>
#include </usr/local/include/glm/gtx/transform.hpp>
#include </usr/include/GL/glew.h>
#include "../Headerfiles/Circle.h"
#include "../Headerfiles/List.h"
#include "../Headerfiles/Rectangle.h"

class Cylinder {
    public:
        Cylinder(glm::vec3 position = glm::vec3{0.0f, 0.0f, 0.0f}, 
               glm::vec3 top = glm::vec3{0.0f, 1.0f, 0.0f}, 
               glm::vec3 radius = glm::vec3{1.0f, 0.0f, 0.0f}, 
               glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
        ~Cylinder();

        void draw();

    private:
        glm::vec3 position;
        glm::vec4 color;

        Circle* d;
        Circle* t;
        List<Rectangle> pList;
};

#endif