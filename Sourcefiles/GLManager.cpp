#include "../Headerfiles/GLManager.h"

GLManager GLManager::s_Instance;

GLManager::GLManager() {
    // Konstruktor-Code hier, falls erforderlich
}

GLManager& GLManager::getInstance() {
    return s_Instance;
}

void GLManager::init() {
    //program = loadShaders("../res/VertexShader.vs", "../res/FragmentShader.fs", "", "", "", "");
    program = loadShaders("../res/VertexShader.vs", "../res/LightPoint.fs", "", "", "", "");
    glUseProgram(program);
}
