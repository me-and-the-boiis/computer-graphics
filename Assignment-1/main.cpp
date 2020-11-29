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
bool toggleLight = 0;

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
    else if (key == 'D' || key == 'd') {
        toggleLight = !toggleLight;
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

void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}


void setupLight() {
    GLfloat light_position[] = { 10.0f, 10.0f, 10.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    
    GLfloat light_position_1[] = { -10.0f, 10.0f, -10.0f, 0.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);
    GLfloat lightIntensity_1[] = { 0.7f, 0.7f, 0.7f, 1.0f };
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
    glViewport(0, 0, screenWidth, screenHeight);

    glRotatef(cameraAngle, 0, 1, 0);
    glScalef(1*cameraDistance, 1*cameraDistance, 1*cameraDistance);

    setupLight();
    drawAxis();

    glColor3f(0, 0, 0);
    if (nChoice == 1) {
        float ambient[] = { 0.105882f, 0.058824f, 0.113725f, 1.0f };
        float diffuse[] = { 0.427451f, 0.470588f, 0.541176f, 1.0f };
        float specular[] = { 0.333333f, 0.333333f, 0.521569f, 1.0f };
        float shininess = 9.84615f;
        setupMaterial(ambient, diffuse, specular, shininess);
        shape1.DrawShape1();
    }
    else if (nChoice == 2) {
        float ambient[] = { 0.1745f, 0.01175f, 0.01175f, 0.55f };
        float diffuse[] = { 0.61424f, 0.04136f, 0.04136f, 0.55f };
        float specular[] = { 0.727811f, 0.626959f, 0.626959f, 0.55f };
        float shininess = 76.8f;
        setupMaterial(ambient, diffuse, specular, shininess);
        shape2.DrawShape2();
    }
    else if (nChoice == 3) {
        float ambient[] = { 0.2295f, 0.08825f, 0.0275f, 1.0f };
        float diffuse[] = { 0.5508f, 0.2118f, 0.066f, 1.0f };
        float specular[] = { 0.580594f, 0.223257f, 0.0695701f, 1.0f };
        float shininess = 51.2f;
        setupMaterial(ambient, diffuse, specular, shininess);
        shape3.DrawShape3();
    }
    else if (nChoice == 4) {
        float ambient[] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
        float diffuse[] = { 0.07568f, 0.61424f, 0.07568f, 0.55f };
        float specular[] = { 0.633f, 0.727811f, 0.633f, 0.55f };
        float shininess = 76.8f;
        setupMaterial(ambient, diffuse, specular, shininess);
        shape4.DrawShape4();
    }
    else if (nChoice == 5) {
        float ambient[] = { 0.05f, 0.05f, 0.05f, 1.0f };
        float diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f};
        float specular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
        float shininess = 10.0f;
        setupMaterial(ambient, diffuse, specular, shininess);
        shape5.DrawShape5(15, 1, 1, 1);
        shape5.Draw();
    }
    
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

