#include <fstream>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>


using namespace std;

//constants
const float WINDOW_WIDTH= 600.0f,
            WINDOW_HEIGHT= 600.0f;

//Variables
float  camPosX, camPosY;
float camPosZ = camPosY= camPosX= 1.0f;
float angle= 0.0f;

//Functions declaration
static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void drawPyramid();
void renderbitmap(float x, float y, void *font, char *string) ;
void writeText(string text );
int main(void) {
    // initialize
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST); //surface transparency
    glOrtho(-90.0, 100.0, -15.0, 100.0, 0.0, -15.0);


    //create GLFW window
    GLFWwindow *window;

    if (!glfwInit()) { // failed to initialize GLFW
        exit(1);
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello GLFW ", 0, NULL);

    if (!window) { //failed to create window
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);


    while (!glfwWindowShouldClose(window)) {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / float(height);
        glViewport(0, 0, width, height);


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-ratio, ratio, -ratio, ratio, 1.0f, 40.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //display
        glTranslated(0.0f, 0.0f, -4.0f);
        gluLookAt(camPosX, camPosY, camPosZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        drawPyramid();
        //text
        //

        glfwSwapBuffers(window);
        glfwPollEvents(); //important
    }

    glfwTerminate();
    return 0;
}

void drawPyramid() {
    glBegin(GL_QUADS);
    glColor3f(38.0f / 255, 48.0f / 255, 67.0f / 255);
    glVertex3f(-1, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 0, -1);
    glVertex3f(-1, 0, -1);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(173.0f / 255, 12.0f / 255, 57.0f / 255);
    glNormal3f(0, 1, 3);
    glVertex3f(0, 3, 0); //head
    glVertex3f(-1, 0, 1);
    glVertex3f(1, 0, 1);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(38.0f / 255, 64.0f / 255, 96.0f / 255);
    glNormal3f(3, 1, 0);
    glVertex3f(0, 3, 0); //head
    glVertex3f(1, 0, 1);
    glVertex3f(1, 0, -1);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(88.0f / 255, 81.0f / 255, 35.0f / 255);
    glNormal3f(0, 1, -3);
    glVertex3f(0, 3, 0); //head
    glVertex3f(1, 0, -1);
    glVertex3f(-1, 0, -1);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(255.0f / 255, 188.0f / 255, 66.0f / 255);
    glNormal3f(-3, 1, 0);
    glVertex3f(0, 3, 0); //head
    glVertex3f(-1, 0, -1);
    glVertex3f(-1, 0, 1);
    glEnd();
}
static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;

            case 265: //up
                camPosY += 1;
                break;

            case 264: //down
                camPosY -= 1;
                break;

            case 262: //right
                camPosX += 1;
                break;

            case 263: // left
                camPosX -= 1;
                break;

            case 32: //space
                camPosZ = camPosY= camPosX= 1.0f;
                break;

            case 82: //R
                angle+=20;
                break;

        }
    }
}
void renderbitmap(float x, float y, void *font, char *string) {
    char *c;
    glRasterPos2f(x, y);
    c = string;
    float u = glutStrokeWidth(font, (int)*c); cout << u << endl;
    glPushMatrix();
    glTranslatef(x-50, y + 50,0);
    glScalef(1.0f, -1.08f,  -14);
    for (c = string; *c != '\0'; c++) {
        //glScalef(0, 0, -3);
        //glutBitmapCharacter(font, (int)*c);
        glutStrokeCharacter(font, (int)*c);
    }
    glPopMatrix();
}

void writeText(string text) {
    glColor3f(1.0f, 1.0f, 0.0f);
    char buf[1000] = { 0 };
    sprintf_s(buf, "kk");//buf[2]=\0;buf[3]=l;
    renderbitmap(0, 50, GLUT_STROKE_ROMAN, buf);
    sprintf_s(buf, "ll");//buf[2]=\0;buf[3]=l;

}
