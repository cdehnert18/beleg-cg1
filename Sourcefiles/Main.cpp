/*
Computergrafik-Erweiterung

Name:	Clemens Dehnert
s-Nr.:	s85492
Mail:	clemensdehnert@gmail.com
*/

/*Includes*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <unordered_map>
#include "../Headerfiles/Camera.h"
#include "../Headerfiles/GLManager.h"
#include "../Headerfiles/Rectangle.h"
#include "../Headerfiles/Cuboid.h"
#include "../Headerfiles/Circle.h"
#include "../Headerfiles/Cone.h"
#include "../Headerfiles/Star.h"
#include "../Headerfiles/Cylinder.h"
#include "../Headerfiles/Geschenk.h"
#include "../Headerfiles/Rad.h"

/*Funktionsdeklarationen*/
void init();
void incrementCounter();
void display();
void reshapeCallback(GLFWwindow* window, int w, int h);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
int main(int argc, char* argv[]);
void renderDown();
void renderTopRight();
void renderTopLeft();

std::unordered_map<int, bool> keys;

/*Szenenelemente*/
Camera myCameraL({-3, 3, 8}, {5, 0, -14}, {0, 1, 0});
Camera myCameraR({2, 1, 8}, {0, 0, -14}, {0, 1, 0});
Camera myCameraD({0, 1, 3});

/*Boden*/
Rectangle* Floor;

/*Weihnachtsbaum*/
Cylinder* Baumstamm;
Cone* Krone1;
Cone* Krone2;
Cone* Krone3;
Star* Stern;

/*Geschenke*/
Geschenk* g1;
Geschenk* g2;
Geschenk* g3;

/*Riesenrad*/
Rad* pRad;
Rectangle* Stuetze;

/*Variable Elemente*/
GLfloat count = 0;
GLfloat fak = 1;

void init() 
{
    GLManager::getInstance().init();
    GLManager::getInstance().width = 720;
    GLManager::getInstance().height = 720;
    myCameraL.setAspectRatio(360.0f / 720.0f);
    myCameraR.setAspectRatio(720.0f / 720.0f);
    myCameraD.setAspectRatio(1440.0f / 720.0f);

    Floor = new Rectangle({0, 0, 0}, {40, 0, 0}, {0, 0, -40}, {1.0f, 1.0f, 1.0f, 1});

    Baumstamm = new Cylinder({0, 0, 0}, {0, 0.1, 0}, {0.1, 0, 0.1}, {102.0f/255.0f, 51.0f/255.0f, 0.0f, 1});
    Krone1 = new Cone({0, 0.1, 0}, {0, 0.4, 0}, {0.5, 0, 0}, {0.0f, 70.0f/255.0f, 0.0f, 1});
    Krone2 = new Cone({0, 0.4, 0}, {0, 0.4, 0}, {0.4, 0, 0}, {0.0f, 70.0f/255.0f, 0.0f, 1});
    Krone3 = new Cone({0, 0.7, 0}, {0, 0.3, 0}, {0.3, 0, 0}, {0.0f, 70.0f/255.0f, 0.0f, 1});
    Stern = new Star({0, 1.2, 0}, {0, 0, -0.1}, {0.1, 0, 0}, {1, 0.8, 0, 1});

    g1 = new Geschenk({-0.3, 0.1, 0.6}, {0.2, 0, 0.1}, {0, 0.2, 0}, {-0.1, 0, 0.2}, {1, 0, 1, 1}, {0, 1, 1, 1});
    g2 = new Geschenk({0.3, 0.1, 0.6}, {0.2, 0, 0.05}, {0, 0.2, 0}, {-0.05, 0, 0.2}, {1, 0, 1, 1}, {0, 1, 1, 1});
    g3 = new Geschenk({0.3, 0.3, 0.6}, {0.2, 0, 0}, {0, 0.2, 0}, {0, 0, 0.2}, {1, 0, 1, 1}, {0, 1, 1, 1});

    pRad = new Rad({0, 0, 0}, {1, 1, 1, 1});
    Stuetze = new Rectangle({0, -0.7, -7}, {-0.6, -3, 1}, {0.6, -3, 1}, {1, 0, 1, 1});
}

void incrementCounter() 
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/30)); // Warte 200 Millisekunden
        count++; // Inkrementiere die globale Variable "Counter"
    }
}

void display()
{
    // Viewports
    for(int i = 0; i < 3; i++) {
        switch(i) {
            case 0: glViewport(0, 0, GLManager::getInstance().width, GLManager::getInstance().height/2);
                    renderDown();
                    break;
            
            case 1: glViewport(0, GLManager::getInstance().height/2, GLManager::getInstance().width/2, GLManager::getInstance().height);
                    renderTopLeft();
                    break;
            
            case 2: glViewport(GLManager::getInstance().width/2, GLManager::getInstance().height/2, GLManager::getInstance().width, GLManager::getInstance().height);
                    renderTopRight();
                    break;
        }
    }
}

void renderDown(){
    // Allgemeines
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 modelMatrixRad = glm::mat4(1.0f);

    modelMatrixRad = glm::translate(modelMatrixRad, glm::vec3(0, 2, -8));
    modelMatrixRad = glm::rotate(modelMatrixRad, glm::radians(- count/fak), glm::vec3(0.0f, 0.0f, 1.0f));
    // Finde die Uniform-Locations im Shader für die Matrizen
    GLuint viewUniform = glGetUniformLocation(GLManager::getInstance().program, "view");
    GLuint projectionUniform = glGetUniformLocation(GLManager::getInstance().program, "projection");
    GLuint modelUniform = glGetUniformLocation(GLManager::getInstance().program, "model");
    GLuint normalUniform = glGetUniformLocation(GLManager::getInstance().program, "NormalMatrix");

    GLuint isTexture = glGetUniformLocation(GLManager::getInstance().program, "isTexture");
    
    /*Initialisierung NormalUniform*/
    glm::mat3 Normal;
	glm::mat4 ModelView = myCameraD.getViewMatrix() * modelMatrixRad;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Normal[i][j] = ModelView[i][j];
		}
	}

    // Sende die Matrizen an den Shader
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, &myCameraD.getViewMatrix()[0][0]);
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, &myCameraD.getProjectionMatrix()[0][0]);
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, &modelMatrixRad[0][0]);
	glUniformMatrix3fv (normalUniform, 1, GL_FALSE, &Normal[0][0]);
    pRad->draw();
    
    /*Initialisierung NormalUniform*/
    ModelView = myCameraD.getViewMatrix() * modelMatrix;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Normal[i][j] = ModelView[i][j];
		}
	}

    // Sende die Matrizen an den Shader
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, &myCameraD.getViewMatrix()[0][0]);
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, &myCameraD.getProjectionMatrix()[0][0]);
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix3fv (normalUniform, 1, GL_FALSE, &Normal[0][0]);

    Stuetze->draw();

    Floor->draw();

    Baumstamm->draw();
    Krone1->draw();
    Krone2->draw();
    Krone3->draw();
    Stern->draw();

    glUniform1i(isTexture, true);
    g1->draw();
    g2->draw();
    g3->draw();
    glUniform1i(isTexture, false);
}

void renderTopRight(){
    // Allgemeines
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 modelMatrixRad = glm::mat4(1.0f);

    modelMatrixRad = glm::translate(modelMatrixRad, glm::vec3(0, 2, -8));
    modelMatrixRad = glm::rotate(modelMatrixRad, glm::radians(- count/fak), glm::vec3(0.0f, 0.0f, 1.0f));

    // Orth
    float left = -3.0f;
    float right = 3.0f;
    float bottom = -1.0f;
    float top = 3.0f;
    float nearPlane = 0.01f;
    float farPlane = 100.0f;

    glm::mat4 projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
    //glm::perspective(glm::radians(this->fov), this->aspectRatio, this->nearClip, this->farClip);

    // Finde die Uniform-Locations im Shader für die Matrizen
    GLuint viewUniform = glGetUniformLocation(GLManager::getInstance().program, "view");
    GLuint projectionUniform = glGetUniformLocation(GLManager::getInstance().program, "projection");
    GLuint modelUniform = glGetUniformLocation(GLManager::getInstance().program, "model");
    GLuint normalUniform = glGetUniformLocation(GLManager::getInstance().program, "NormalMatrix");

    GLuint isTexture = glGetUniformLocation(GLManager::getInstance().program, "isTexture");
    
    /*Initialisierung NormalUniform*/
    glm::mat3 Normal;
	glm::mat4 ModelView = myCameraR.getViewMatrix() * modelMatrixRad;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Normal[i][j] = ModelView[i][j];
		}
	}

    // Sende die Matrizen an den Shader
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, &myCameraR.getViewMatrix()[0][0]);
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, &modelMatrixRad[0][0]);
	glUniformMatrix3fv (normalUniform, 1, GL_FALSE, &Normal[0][0]);
    pRad->draw();
    
    /*Initialisierung NormalUniform*/
    ModelView = myCameraR.getViewMatrix() * modelMatrix;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Normal[i][j] = ModelView[i][j];
		}
	}

    // Sende die Matrizen an den Shader
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, &myCameraR.getViewMatrix()[0][0]);
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix3fv (normalUniform, 1, GL_FALSE, &Normal[0][0]);

    Stuetze->draw();

    Floor->draw();

    Baumstamm->draw();
    Krone1->draw();
    Krone2->draw();
    Krone3->draw();
    Stern->draw();

    glUniform1i(isTexture, true);
    g1->draw();
    g2->draw();
    g3->draw();
    glUniform1i(isTexture, false);
}

void renderTopLeft(){
    // Allgemeines
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 modelMatrixRad = glm::mat4(1.0f);

    modelMatrixRad = glm::translate(modelMatrixRad, glm::vec3(0, 2, -8));
    modelMatrixRad = glm::rotate(modelMatrixRad, glm::radians(- count/fak), glm::vec3(0.0f, 0.0f, 1.0f));
    // Finde die Uniform-Locations im Shader für die Matrizen
    GLuint viewUniform = glGetUniformLocation(GLManager::getInstance().program, "view");
    GLuint projectionUniform = glGetUniformLocation(GLManager::getInstance().program, "projection");
    GLuint modelUniform = glGetUniformLocation(GLManager::getInstance().program, "model");
    GLuint normalUniform = glGetUniformLocation(GLManager::getInstance().program, "NormalMatrix");

    GLuint isTexture = glGetUniformLocation(GLManager::getInstance().program, "isTexture");
    
    /*Initialisierung NormalUniform*/
    glm::mat3 Normal;
	glm::mat4 ModelView = myCameraL.getViewMatrix() * modelMatrixRad;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Normal[i][j] = ModelView[i][j];
		}
	}

    // Sende die Matrizen an den Shader
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, &myCameraL.getViewMatrix()[0][0]);
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, &myCameraL.getProjectionMatrix()[0][0]);
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, &modelMatrixRad[0][0]);
	glUniformMatrix3fv (normalUniform, 1, GL_FALSE, &Normal[0][0]);
    pRad->draw();
    
    /*Initialisierung NormalUniform*/
    ModelView = myCameraL.getViewMatrix() * modelMatrix;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Normal[i][j] = ModelView[i][j];
		}
	}

    // Sende die Matrizen an den Shader
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, &myCameraL.getViewMatrix()[0][0]);
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, &myCameraL.getProjectionMatrix()[0][0]);
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix3fv (normalUniform, 1, GL_FALSE, &Normal[0][0]);

    Stuetze->draw();

    Floor->draw();

    Baumstamm->draw();
    Krone1->draw();
    Krone2->draw();
    Krone3->draw();
    Stern->draw();

    glUniform1i(isTexture, true);
    g1->draw();
    g2->draw();
    g3->draw();
    glUniform1i(isTexture, false);
}

void reshapeCallback(GLFWwindow* window, int w, int h) 
{
    GLManager::getInstance().width = w;
    GLManager::getInstance().height = h;

    myCameraL.setAspectRatio(static_cast<float>(GLManager::getInstance().width/2) / static_cast<float>(GLManager::getInstance().height));
    myCameraR.setAspectRatio(static_cast<float>(GLManager::getInstance().width) / static_cast<float>(GLManager::getInstance().height));
    myCameraD.setAspectRatio(static_cast<float>(GLManager::getInstance().width*2) / static_cast<float>(GLManager::getInstance().height));
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    static float old_x = xpos;
    static float old_y = ypos;

    float xOffset = static_cast<float>(xpos - old_x);
    float yOffset = static_cast<float>(old_y - ypos);

    float sensitivity = 0.004f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    glm::vec3 cameraFront = glm::normalize(myCameraD.target - myCameraD.position);
    glm::vec3 right = glm::normalize(glm::cross(cameraFront, myCameraD.up));

    glm::vec3 newFront = cameraFront * static_cast<float>(cos(yOffset)) + myCameraD.up * static_cast<float>(sin(yOffset));
    cameraFront = glm::normalize(newFront);
    cameraFront = cameraFront * static_cast<float>(cos(xOffset)) + right * static_cast<float>(sin(xOffset));

    myCameraD.target = myCameraD.position + cameraFront;

    myCameraD.setTarget({myCameraD.target.x, myCameraD.target.y, myCameraD.target.z});
    
    old_x = xpos;
    old_y = ypos;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        keys[key] = true; // Wenn Taste gedrückt wird, speichere den Zustand als gedrückt
    } else if (action == GLFW_RELEASE) {
        keys[key] = false; // Wenn Taste losgelassen wird, speichere den Zustand als nicht gedrückt
    }
    glm::vec3 cameraToTarget = glm::normalize(myCameraD.target - myCameraD.position);
    glm::vec3 right = glm::normalize(glm::cross(cameraToTarget, myCameraD.up));

    float moveSpeed = 1.0f; // Geschwindigkeit der Kamerabewegung
    float deltaTime = 0.016f; // Zeit zwischen den Frames, anpassen, falls eine andere Zeitschrittgröße verwendet wird

    switch (key) {
        case GLFW_KEY_W:
            myCameraD.setPosition(myCameraD.position + cameraToTarget * moveSpeed * deltaTime);
            break;
        case GLFW_KEY_A:
            myCameraD.setPosition(myCameraD.position - right * moveSpeed * deltaTime);
            break;
        case GLFW_KEY_S:
            myCameraD.setPosition(myCameraD.position - cameraToTarget * moveSpeed * deltaTime);
            break;
        case GLFW_KEY_D:
            myCameraD.setPosition(myCameraD.position + right * moveSpeed * deltaTime);
            break;
        case GLFW_KEY_Q:
            myCameraD.setPosition(myCameraD.position - myCameraD.up * moveSpeed * deltaTime);
            break;
        case GLFW_KEY_E:
            myCameraD.setPosition(myCameraD.position + myCameraD.up * moveSpeed * deltaTime);
            break;
        case GLFW_KEY_R:
            fak *= 1.2f;
            break;
        case GLFW_KEY_G:
            fak *= 0.8f;
            break;
    }
}

int main(int argc, char* argv[])
{
    std::thread counterThread(incrementCounter);

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Hauptversion (hier 4)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Nebenversion (hier 5)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(720, 720, "GLFW Application", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
    {
        std::cout << "Error" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    init();

    /* Setze den Callbacks */
    glfwSetFramebufferSizeCallback(window, reshapeCallback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, keyCallback);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glEnable(GL_BLEND);

        display();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    counterThread.join();
    return 0;
}