// Bai3.cpp : Defines the entry point for the console application.
//

#define GL_SILENCE_DEPRECATION

//#include <GLUT/GLUT.h>

#include <gl/gl.h>
#include <gl/glut.h>
#include <windows.h>

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

#define PI 3.1415926

using namespace std;

int        screenWidth = 600;
int        screenHeight= 600;

Mesh    shape1;
Mesh    shape2;
Mesh    shape3;
Mesh    shape4;
Mesh    shape5;

int        nChoice = 1;

float cameraAngle = 45;
float cameraHeight = 0;
float cameraDistance = 1.25;

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
    }
    glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y) {
    if (key == '+') {
        cameraDistance += 0.05;
    }
    else if (key == '-') {
        cameraDistance -= 0.05;
    }
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
    glViewport(0, 0, screenWidth, screenHeight);

    glRotatef(cameraAngle, 0, 1, 0);
    glScalef(1*cameraDistance, 1*cameraDistance, 1*cameraDistance);

    drawAxis();

    glColor3f(0, 0, 0);
    if (nChoice == 1)
        shape1.DrawShape1();
    else if (nChoice == 2)
        shape2.DrawShape2();
    else if (nChoice == 3)
        shape3.DrawShape3();
    else if (nChoice == 4)
        shape4.DrawShape4();
    else if (nChoice == 5)
        shape5.DrawShape5();


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

    glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
    gluLookAt(20, 20, 20, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char* argv[])
{
    cout << "1. Draw shape 1" << endl;
    cout << "2. Draw shape 2" << endl;
    cout << "3. Draw shape 3" << endl;
    cout << "4. Draw shape 4" << endl;
    cout << "5. Draw shape 5" << endl;
    cout << "Input the choice: " << endl;
    cin  >> nChoice;

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

