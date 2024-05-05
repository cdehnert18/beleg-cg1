#include "../Headerfiles/Geschenk.h"
#include "../Headerfiles/Rectangle.h"
#include "../Headerfiles/GLManager.h"
#include <iostream>

Geschenk::Geschenk(glm::vec3 position, glm::vec3 sideA, glm::vec3 sideB, glm::vec3 sideC, glm::vec4 color1, glm::vec4 color2) {
    d = new Texture(position - 0.5f * sideB, sideA, sideC, color1, color2);
    f = new Texture(position + 0.5f * sideC, sideA, sideB, color1, color2);
    b = new Texture(position - 0.5f * sideC, sideB, sideA, color1, color2);
    l = new Texture(position -0.5f * sideA, sideC, sideB, color1, color2);
    r = new Texture(position + 0.5f * sideA, sideB, sideC, color1, color2);
    t = new Texture(position + 0.5f * sideB, sideC, sideA, color1, color2);
}

Geschenk::~Geschenk() {
    delete d;
    delete f;
    delete b;
    delete l;
    delete r;
    delete t;
}

void Geschenk::draw() {
    d->draw();
    f->draw();
    b->draw();
    l->draw();
    r->draw();
    t->draw();
}