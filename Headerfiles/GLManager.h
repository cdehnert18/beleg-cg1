#ifndef GLMANAGER_H
#define GLMANAGER_H

#include <GL/glew.h>

GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath,
    const char* tesscontrolFilePath, const char* tessevaluationFilePath, const char* computeFilePath);

class GLManager {
public:
    GLManager(const GLManager&) = delete;

    static GLManager& getInstance();

    void init();

    static GLManager s_Instance;

    GLfloat height = 100;
    GLfloat width = 100;
    enum Attrib_IDs { vPosition, vColor, vNormal, vTexture };
    GLuint program;

private:
    GLManager();

};

#endif // GLMANAGER_H
