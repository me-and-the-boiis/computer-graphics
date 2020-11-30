// Bai3.cpp : Defines the entry point for the console application.
//

#define GL_SILENCE_DEPRECATION

#include <GLUT/GLUT.h>

//#include <gl/gl.h>
//#include <gl/glut.h>
//#include <windows.h>

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

#define PI 3.1415926

using namespace std;

int        screenWidth = 800;
int        screenHeight= 800;

float cameraAngle = 45;
float cameraHeight = 0;
float cameraDistance = 0.25;
bool toggleLight = 0;
float shape2Angle = 0;
bool drawFlag = 0;

void mySpecialFunc(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        cameraAngle += 3;
    }
    else if (key == GLUT_KEY_RIGHT) {
        cameraAngle -= 3;
    }
    else if (key == GLUT_KEY_UP) {
        cameraHeight += 0.25;
    }
    else if (key == GLUT_KEY_DOWN) {
        cameraHeight -= 0.25;
    } else return;
    glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y) {
    if (key == '+') {
        cameraDistance += 0.05;
    }
    else if (key == '-') {
        cameraDistance -= 0.05;
    }
    else if (key == 'D' || key == 'd') {
        toggleLight = !toggleLight;
    } else if (key == '1') {
        //-20->14
        shape2Angle +=shape2Angle<0;
    } else if (key == '2') {
        shape2Angle -=shape2Angle>-24;
    }
    else if (key == 'W' || key == 'w') {
        drawFlag = !drawFlag;
    } else return;
    glutPostRedisplay();
}

void drawAxis()
{
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(4, 0, 0);

        glVertex3f(0, 0, 0);
        glVertex3f(0, 4, 0);

        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 4);
    glEnd();
}

void setupLight() {
    GLfloat light_position[] = { 10.0f, 10.0f, 10.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

    GLfloat light_position_1[] = { -10.0f, 10.0f, -10.0f, 0.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);
    GLfloat lightIntensity_1[] = { 0.55f, 0.55f, 0.55f, 0.7f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity_1);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    if (toggleLight) {
        glEnable(GL_LIGHT1);
    } else {
        glDisable(GL_LIGHT1);
    }
    glShadeModel(GL_FLAT);

    glEnable(GL_NORMALIZE);
}

void myDisplay()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
          cameraDistance*cos(cameraAngle/360*2*PI),
          cameraHeight,
          cameraDistance*sin(cameraAngle/360*2*PI),
          0.0, 0.0, 0.0, 0, 1, 0
    );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, screenWidth*2, screenHeight*2);

    glRotatef(cameraAngle, 0, 1, 0);
    glScalef(1*cameraDistance, 1*cameraDistance, 1*cameraDistance);
    
    setupLight();
    drawAxis();

    glColor3f(0, 0, 0);
//    cout << 1;
    Mesh mesh;
    mesh.BigDraw(shape2Angle);

//    Mesh bigboi;
//    bigboi.DrawMechanicDevice(drawFlag, nChoice);
    glFlush();
    glutSwapBuffers();
}

void myInit()
{
    float    fHalfSize = 8;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-fHalfSize/2, fHalfSize/2, -fHalfSize/2, fHalfSize/2, -1000, 1000);
//    gluLookAt(20, 20, 20, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char* argv[])
{
//    cout << "1. Draw shape 1" << endl;
//    cout << "2. Draw shape 2" << endl;
//    cout << "3. Draw shape 3" << endl;
//    cout << "4. Draw shape 4" << endl;
//    cout << "5. Draw shape 5" << endl;
//    cout << "Input the choice: " << endl;
////    cin  >> nChoice;

    glutInit(&argc, (char**)argv); //initialize the tool kit
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
    glutInitWindowSize(screenWidth, screenHeight); //set window size
    glutInitWindowPosition(100, 100); // set window position on screen
    glutCreateWindow("Lab 2"); // open the screen window

    myInit();
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(mySpecialFunc);
    glutKeyboardFunc(myKeyboard);

    glutMainLoop();
    return 0;
}

