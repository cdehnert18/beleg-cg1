#include "../Headerfiles/Cuboid.h"
#include "../Headerfiles/Rectangle.h"
#include "../Headerfiles/GLManager.h"
#include <iostream>

Cuboid::Cuboid(glm::vec3 position, glm::vec3 sideA, glm::vec3 sideB, glm::vec3 sideC, glm::vec4 color) {
    d = new Rectangle(position - 0.5f * sideB, sideA, sideC, color);
    f = new Rectangle(position + 0.5f * sideC, sideA, sideB, color);
    b = new Rectangle(position - 0.5f * sideC, sideB, sideA, color);
    l = new Rectangle(position -0.5f * sideA, sideC, sideB, color);
    r = new Rectangle(position + 0.5f * sideA, sideB, sideC, color);
    t = new Rectangle(position + 0.5f * sideB, sideC, sideA, color);
}

Cuboid::~Cuboid() {
    delete d;
    delete f;
    delete b;
    delete l;
    delete r;
    delete t;
}

void Cuboid::draw() {
    d->draw();
    f->draw();
    b->draw();
    l->draw();
    r->draw();
    t->draw();
}