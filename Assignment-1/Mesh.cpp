#define GL_SILENCE_DEPRECATION

#include "Mesh.h"
#include <math.h>
#include <iostream>

#define PI            3.1415926
#define    COLORNUM        14

float radianToDegree(float radian) {
    return radian*180/PI;
}

void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

float    ColorArr[COLORNUM][3] = {
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 1.0, 0.0},
    {1.0, 0.0, 1.0},
    {0.0, 1.0, 1.0},
    {0.3, 0.3, 0.3},
    {0.5, 0.5, 0.5},
    {0.9, 0.9, 0.9},
    {1.0, 0.5, 0.5},
    {0.5, 1.0, 0.5},
    {0.5, 0.5, 1.0},
    {0.0, 0.0, 0.0},
    {1.0, 1.0, 1.0}
};

void Mesh::CreatePizza(int nSegment, float Angle, float fHeight, float fRadius) {
    int numSegment = roundf(Angle/(2*PI)*nSegment);
	numVerts=nSegment*2 + 2;
	pt = new Point3[numVerts];
	int		i;
	int		idx;
	float	fAngle = 2*PI/nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight, 0);
	for(i = 0; i<nSegment; i++)
	{
		x = fRadius* cos(fAngle*i);
		z = fRadius* sin(fAngle*i);
		y = fHeight;
		pt[i+1].set(x, y, z);

		y = 0;
		pt[i +1 + nSegment].set(x, y, z);
	}
	pt[numVerts-1].set(0, 0, 0);


	if (numSegment*3 < nSegment*3) {
        numFaces = numSegment*3+2;
        face = new Face[numFaces];
        face[numFaces-1].nVerts = 4;
        face[numFaces-1].vert = new VertexID[4];
        face[numFaces-1].vert[0].vertIndex = 0;
        face[numFaces-1].vert[1].vertIndex = numVerts - 1;
        face[numFaces-1].vert[2].vertIndex = nSegment + 1;
        face[numFaces-1].vert[3].vertIndex = 1;
        face[numFaces-2].nVerts = 4;
        face[numFaces-2].vert = new VertexID[4];
        face[numFaces-2].vert[0].vertIndex = 0;
        face[numFaces-2].vert[1].vertIndex = numVerts - 1;
        face[numFaces-2].vert[2].vertIndex = nSegment + 1 + numSegment;
        face[numFaces-2].vert[3].vertIndex = numSegment + 1;
	} else {
        numFaces= nSegment*3;
        face = new Face[numFaces];
	}

	idx = 0;
	for(i = 0; i<numSegment; i++)
	{
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = 0;
        face[i].vert[1].vertIndex = i < nSegment -1 ? i + 2 : 1;
		face[i].vert[2].vertIndex = i + 1;

        face[numSegment+i].nVerts = 4;
		face[numSegment+i].vert = new VertexID[face[numSegment+i].nVerts];
		face[numSegment+i].vert[0].vertIndex = i+1;
        face[numSegment+i].vert[1].vertIndex = i < nSegment - 1 ? i + 2 : 1;
		face[numSegment+i].vert[2].vertIndex = face[numSegment+i].vert[1].vertIndex + nSegment;
		face[numSegment+i].vert[3].vertIndex = face[numSegment+i].vert[0].vertIndex + nSegment;

        face[2*numSegment+i].nVerts = 3;
		face[2*numSegment+i].vert = new VertexID[face[2*numSegment+i].nVerts];
		face[2*numSegment+i].vert[0].vertIndex = numVerts - 1;
        face[2*numSegment+i].vert[2].vertIndex = i < nSegment -1 ? i + 2 + nSegment  : 1 + nSegment;
		face[2*numSegment+i].vert[1].vertIndex = i + 1 + nSegment;
	}

    CalculateFacesNorm();
}

void Mesh::CreateJoint(int nSegment, float fWidth, float fLength, float fHeight) {
    numVerts = nSegment * 4 + 4;
    pt = new Point3[numVerts];

    float fAngle = PI/nSegment;
    float x, y, z;

    for (int i = 0; i < nSegment + 1; i++) {
        float r = fWidth/2;

        x = -(r * sin(fAngle*i) + fLength/2);
        z = r * cos(fAngle*i);
        y = fHeight/2;
        pt[i].set(x, y, z);
        pt[2 * nSegment + 1 - i].set(-x, y, z);
        pt[2 * nSegment + 2 + i].set(x, -y, z);
        pt[4 * nSegment + 3 - i].set(-x, -y, z);
    }

    numFaces = 2 * nSegment + 4;
    face = new Face[numFaces];

//        Assign points for top and bottom faces
    face[0].nVerts = 2 * nSegment + 2;
    face[0].vert = new VertexID[face[0].nVerts];
    face[1].nVerts = 2 * nSegment + 2;
    face[1].vert = new VertexID[face[1].nVerts];

    int idx = 2;
//        Draw top and bottom faces
    for (int i = 0; i < 2 * nSegment + 2; i++) {
        face[0].vert[i].vertIndex = i;
        face[1].vert[i].vertIndex = 2 * nSegment + 2 + i;

//        Draw side faces
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i;
        face[idx].vert[1].vertIndex =
            i == 2 * nSegment + 1 ? 0 : i + 1;
        face[idx].vert[2].vertIndex =
            i == 2 * nSegment + 1 ? i + 1 : 2 * nSegment + 3 + i;
        face[idx].vert[3].vertIndex = 2 * nSegment + 2 + i;
        idx++;
    }

    CalculateFacesNorm();
}

void Mesh::CreatePismatic(float fHeight, float x, float x0, float z0, float x1, float z1)
{
    if ((x1 == -10) && (z0 != -10) && (x0 != -10))
        numFaces=5;
    else
        numFaces=6;

    if (x0 == -10) {
        x0 = x;
        z0 = x;
        x1 = 0;
        z1 = x;
    } else {
        if (z0 == -10) {
            x1 = 0;
            z1 = x0;
            z0 = x0;
            x0 = x;
        } else {
            x1 = x1==-10?0:x1;
            z1 = z1==-10?0:z1;
        }
    }

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(0, fHeight, 0);
	pt[1].set( x, fHeight, 0);
	pt[2].set( x0, fHeight, z0);
	pt[3].set(x1, fHeight, z1);
	pt[4].set(0, 0, 0);
	pt[5].set( x, 0, 0);
	pt[6].set( x0, 0, z0);
	pt[7].set(x1, 0, z1);

	face = new Face[6];

    face[0].nVerts = 4;
    face[1].nVerts = 4;
    face[0].vert = new VertexID[4];
    face[1].vert = new VertexID[4];

    for (int i = 0; i<4; i++) {
        face[0].vert[i].vertIndex = 3-i;
        face[1].vert[i].vertIndex = 4+i;
        face[i+2].nVerts = 4;
        face[i+2].vert = new VertexID[4];
        face[i+2].vert[0].vertIndex = i;
        face[i+2].vert[1].vertIndex = i < 3 ? i + 1 : 0;
		face[i+2].vert[2].vertIndex = i < 3 ? 5 + i : 4;
		face[i+2].vert[3].vertIndex = 4 + i;
    }

    CalculateFacesNorm();
}

void Mesh::DrawCylinder() {
    float ambient[] = { 0.205882f, 0.158824f, 0.813725f, 1.0f };
    float diffuse[] = { 0.427451f, 0.470588f, 0.541176f, 1.0f };
    float specular[] = { 0.333333f, 0.333333f, 0.521569f, 1.0f };
    float shininess = 9.84615f;
    setupMaterial(ambient, diffuse, specular, shininess);

    const float height = 1.2;
    glPushMatrix();
    Mesh pizza2PI;
    pizza2PI.CreatePizza(20, 2*PI, height, 0.25);
    pizza2PI.Draw();
    glPopMatrix();
}
void Mesh::DrawShape0() {
    const float height = 1.2;
    glPushMatrix();
//    glTranslated();
    Mesh pismaticBody;
    pismaticBody.CreatePismatic(height, 3, 16);
    pismaticBody.Draw();
    glPopMatrix();
}

void Mesh::DrawShape1() {
    float ambient[] = { 0.105882f, 0.058824f, 0.113725f, 1.0f };
    float diffuse[] = { 0.427451f, 0.470588f, 0.541176f, 1.0f };
    float specular[] = { 0.333333f, 0.333333f, 0.521569f, 1.0f };
    float shininess = 9.84615f;
    setupMaterial(ambient, diffuse, specular, shininess);

    const float height = 0.5;
    glPushMatrix();

    Mesh pismaticBody;
    pismaticBody.CreatePismatic(height, 1.5, 1, 7, 0, 7);
    pismaticBody.Draw();
    glTranslatef(0, 0, 7);

    Mesh pizzaPidiv2;
    pizzaPidiv2.CreatePizza(20, PI/2, height, 1);
    pizzaPidiv2.Draw();

    glPopMatrix();
}

void Mesh::DrawShape2() {
    float ambient[] = { 0.405882f, 0.458824f, 0.913725f, 1.0f };
    float diffuse[] = { 0.427451f, 0.470588f, 0.541176f, 1.0f };
    float specular[] = { 0.333333f, 0.333333f, 0.521569f, 1.0f };
    float shininess = 9.84615f;
    const float height = 0.5;
    glPushMatrix();
    Mesh pizzaPi;
    glTranslatef(0.6, 0, 6);
    pizzaPi.CreatePizza(20, PI, height, 0.5);
    if (drawMeshFlag) {
        pizzaPi.DrawWireframe();
    } else {
        pizzaPi.Draw();
    }
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1, -1);
    glPushMatrix();
    glTranslatef(0.35, 0, 0);
    Mesh pismaticBody1;
    pismaticBody1.CreatePismatic(height, 0.5, 0.6, 1.5, -0.1, 1.5);
    if (drawMeshFlag) {
        pismaticBody1.DrawWireframe();
    } else {
        pismaticBody1.Draw();
    }
    glPopMatrix();

    Mesh pizzaSmal;
    glTranslatef(0.6, 0, 1.5);
    pizzaSmal.CreatePizza(20, PI, height, 0.35);
    if (drawMeshFlag) {
        pizzaSmal.DrawWireframe();
    } else {
        pizzaSmal.Draw();
    }
    glPopMatrix();

    Mesh pismaticBody;
    pismaticBody.CreatePismatic(height, 1.2, 1.1, 6, .1, 6);
    pismaticBody.Draw();
    if (drawMeshFlag) {
        pismaticBody.DrawWireframe();
    } else {
        pismaticBody.Draw();
    }
}

void Mesh::DrawShape3() {

    float ambient[] = { 0.2295f, 0.08825f, 0.0275f, 1.0f };
    float diffuse[] = { 0.5508f, 0.2118f, 0.066f, 1.0f };
    float specular[] = { 0.580594f, 0.223257f, 0.0695701f, 1.0f };
    float shininess = 51.2f;
    setupMaterial(ambient, diffuse, specular, shininess);

    const float height = 0.5;
    glPushMatrix();
    Mesh fourthQuad;
    fourthQuad.CreatePismatic(height, 1, 4);
    fourthQuad.Draw();

    glTranslatef(0, 0, 4);
    Mesh secondQuad;
    secondQuad.CreatePismatic(height, 1, 1.5, 1, 0, 2);
    secondQuad.Draw();

    float alpha = atan(0.5);
    glTranslatef(1.5, 0, 1);
    glRotatef(2*alpha/(2*PI)*360, 0, 1, 0);
    glScalef(-1, 1, 1);
    glRotatef(180, 0, 1, 0);
    Mesh thirdTriangle;
    thirdTriangle.CreatePismatic(height, 0.5, 0.5, 1);
    thirdTriangle.Draw();

    glRotatef(180, 0, 1, 0);
    glScalef(-1, 1, 1);
    Mesh pizza2div3PI;
    pizza2div3PI.CreatePizza(30, 2*PI/3, height, 0.5);
    pizza2div3PI.Draw();

    float alpha3 = 2*PI - (atan(2)*2+atan(2./3)+2*PI/3);
    glRotatef(-(120+alpha3/(2*PI)*360), 0, 1, 0);
    glScalef(-1, 1, 1);
    glRotatef(180, 0, 1, 0);

    Mesh firstTriangle;
    firstTriangle.CreatePismatic(height, sqrt(1+1.5*1.5), 0.5*cos(alpha3), 0.5*sin(alpha3));
    firstTriangle.Draw();

    glPopMatrix();
}

void Mesh::DrawShape5() {
    float ambient[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    float diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f};
    float specular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    float shininess = 10.0f;
    setupMaterial(ambient, diffuse, specular, shininess);

    glPushMatrix();
    Mesh shape5;
    shape5.CreateShape5(20, 1, 2, 0.5);
    glTranslatef(0,-0.25,0);
    shape5.Draw();
    glPopMatrix();
}

void Mesh::DrawShape4() {
    float ambient[] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
    float diffuse[] = { 0.07568f, 0.61424f, 0.07568f, 0.55f };
    float specular[] = { 0.633f, 0.727811f, 0.633f, 0.55f };
    float shininess = 76.8f;
    setupMaterial(ambient, diffuse, specular, shininess);

    const float height = 0.5;
    glPushMatrix();
    Mesh fourthQuad;
    float h = sqrt(1.2*1.2+1-0.7*0.7);
    float xPoint2 = 2.7 + sqrt(1.2*1.2+1-0.7*0.7);
    fourthQuad.CreatePismatic(height, 2.7, xPoint2, 0.7, 0, 3);
    fourthQuad.Draw();

    glTranslatef(2.7, 0, 0);

    float a = sqrt(1.2*1.2+0.5*0.5);
    float b = sqrt(1.2*1.2+1);
    float beta = acos((a*a+b*b-0.5*0.5)/(2*a*b));
    float miniAlpha = PI/2 - beta - atan(h/0.7);
    float alpha = atan(0.5/1.2) - miniAlpha;

    glRotatef(radianToDegree(alpha), 0, 1, 0);

    Mesh firstTriangle;
    firstTriangle.CreatePismatic(height, 1.2, 1.2, 1);
    firstTriangle.Draw();

    glTranslatef(1.2, 0, 0.5);
    glRotatef(90, 0, 1, 0);
    Mesh pizzaPi;
    pizzaPi.CreatePizza(30, PI, height, 0.5);
    pizzaPi.Draw();
    glPopMatrix();
}

void Mesh::CreateShape5(int nSegment, float fWidth, float fLength, float fHeight) {
    numVerts = nSegment * 4 + 4;
    pt = new Point3[numVerts];

    float fAngle = PI/nSegment;
    float x, y, z;

    for (int i = 0; i < nSegment + 1; i++) {
        float r = fWidth/2;

        x = -(r * sin(fAngle*i) + fLength/2);
        z = r * cos(fAngle*i);
        y = fHeight/2;
        pt[i].set(x, y, z);
        pt[2 * nSegment + 1 - i].set(-x, y, z);
        pt[2 * nSegment + 2 + i].set(x, -y, z);
        pt[4 * nSegment + 3 - i].set(-x, -y, z);
    }

    numFaces = 2 * nSegment + 4;
    face = new Face[numFaces];

//        Assign points for top and bottom faces
    face[0].nVerts = 2 * nSegment + 2;
    face[0].vert = new VertexID[face[0].nVerts];
    face[1].nVerts = 2 * nSegment + 2;
    face[1].vert = new VertexID[face[1].nVerts];

    int idx = 2;
//        Draw top and bottom faces
    for (int i = 0; i < 2 * nSegment + 2; i++) {
        face[0].vert[i].vertIndex = i;
        face[1].vert[i].vertIndex = 2 * nSegment + 2 + i;

//        Draw side faces
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = i;
        face[idx].vert[1].vertIndex =
            i == 2 * nSegment + 1 ? 0 : i + 1;
        face[idx].vert[2].vertIndex =
            i == 2 * nSegment + 1 ? i + 1 : 2 * nSegment + 3 + i;
        face[idx].vert[3].vertIndex = 2 * nSegment + 2 + i;
        idx++;
    }
    CalculateFacesNorm();
}

void Mesh::DrawWireframe()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for (int f = 0; f < numFaces; f++)
    {
        glBegin(GL_POLYGON);
        for (int v = 0; v < face[f].nVerts; v++)
        {
            int    iv = face[f].vert[v].vertIndex;

            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
}

void Mesh::DrawColor()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (int f = 0; f < numFaces; f++)
    {
        glBegin(GL_POLYGON);
        for (int v = 0; v < face[f].nVerts; v++)
        {
            int        iv = face[f].vert[v].vertIndex;
            int        ic = face[f].vert[v].colorIndex;

            ic = f % COLORNUM;

            glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
}

void Mesh::CalculateFacesNorm() {
    float   mx, my, mz;
    int     idx, next;

    for (int f = 0; f < numFaces; f++)
    {
        mx = 0;
        my = 0;
        mz = 0;
        for (int v = 0; v < face[f].nVerts; v++)
        {
            idx = v;
            next = (idx + 1) % face[f].nVerts;

            int p1 = face[f].vert[idx].vertIndex;
            int p2 = face[f].vert[next].vertIndex;

            mx = mx + (pt[p1].y - pt[p2].y)*(pt[p1].z + pt[p2].z);
            my = my + (pt[p1].z - pt[p2].z)*(pt[p1].x + pt[p2].x);
            mz = mz + (pt[p1].x - pt[p2].x)*(pt[p1].y + pt[p2].y);

        }
        face[f].facenorm.set(mx, my, mz);
        face[f].facenorm.normalize();
    }
}

void Mesh::Draw() {
    for (int f = 0; f < numFaces; f++){
        glBegin(GL_POLYGON);
        for (int v = 0; v < face[f].nVerts; v++){
            int iv = face[f].vert[v].vertIndex;
            glNormal3f(
               face[f].facenorm.x,
               face[f].facenorm.y,
               face[f].facenorm.z
            );
            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
}


void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}


void Mesh::BigDraw(float shape2Angle) {
    float h = sqrt(1.2*1.2+1-0.7*0.7);
    float xPoint2 = 2.7 + sqrt(1.2*1.2+1-0.7*0.7);
    float a2 = sqrt(1.2*1.2+0.5*0.5);
    float b = sqrt(1.2*1.2+1);
    float beta = acos((a2*a2+b*b-0.5*0.5)/(2*a2*b));
    float miniAlpha = PI/2 - beta - atan(h/0.7);
    float xT = a2*sin(miniAlpha);
    std::cout << xT << ' ' << std::endl;
    float angle1, angle2, angle0;
    {
        float shape2AngleR = shape2Angle*PI/180;
        float L1 = 3, L2 = 2, L3 = 2.9;
        float b = 2.5, a = 5.5 + xT;
        angle0 = atan(b/a);
        float c = sqrt(a*a+b*b);
        float c1 = L1*sin(shape2AngleR), c2 = L1*cos(shape2AngleR);
//        std::cout << c1 << ' ' << c2 << std::endl;
        float alpha1 = atan(c1/(c-c2));

        float m = sqrt(c1*c1+(c-c2)*(c-c2));
        float alpha2 = acos((L3*L3+m*m-L2*L2)/(2*L3*m));
        float alpha3 = alpha2 - (atan(b/a) - alpha1);
        float alpha4 = acos((L3*L3+L2*L2-m*m)/(2*L3*L2));
        std::cout << m << radianToDegree(alpha4) << std::endl;
        angle1 = alpha3; angle2 = alpha4;

        std::cout << radianToDegree(shape2AngleR) << ' ' << radianToDegree(angle1) << ' ' << radianToDegree(angle2) << std::endl;
    }


    Mesh    shape;
    int nChoice = 0;
    float ambient[] = { 0.105882f, 0.558824f, 0.113725f, 1.0f };
    float diffuse[] = { 0.427451f, 0.470588f, 0.541176f, 1.0f };
    float specular[] = { 0.333333f, 0.333333f, 0.521569f, 1.0f };
    float shininess = 9.84615f;
    glPushMatrix();
    setupMaterial(ambient, diffuse, specular, shininess);
    glTranslatef(-1.5, 0, -8);
    shape.DrawShape0();

    glTranslatef(1.5+0.25, 1.2, 11.5);
    glRotated(90, 0 , 0, 1);
    shape.DrawShape4();
    glPushMatrix();
    float a = sqrt(1.2*1.2+0.5*0.5-1.3*1.3);
    glTranslatef(0, 0, -10.5);
    shape.DrawShape3();

    glScalef(1, -1, -1);
//    glTranslatef(0.7, 0, 4.5);

    glTranslatef(1.5, -0.6, -5);
    shape.DrawCylinder();
    glTranslatef(0, 0.6, 0);
    glRotated(radianToDegree(angle1), 0, 1, 0);//
    glTranslatef(-0.7, 0, -3.5);

    shape.DrawShape1();
    glTranslatef(0.7, 0, 0.6);
    glScalef(1, -1, -1);
    glTranslatef(0, -0.6, 0);
    shape.DrawCylinder();

    glRotatef(90-radianToDegree(angle2), 0, 1, 0); //
//    glRotatef(5, 0, 1, 0);
    glTranslatef(1, 1.1, 0);
    shape.DrawShape5();
    glTranslatef(1, -1.1, 0);

    shape.DrawCylinder();
    glPopMatrix();

    glTranslatef(4, -0.6, xT);

    shape.DrawCylinder();
    glScalef(1, 1, -1);
    glRotated(-shape2Angle - radianToDegree(angle0), 0, 1, 0);//

    glTranslatef(-0.6, 0.1, -3);
//    glTranslatef()

    shape.DrawShape2();

    if (nChoice == 1) {
        shape.DrawShape1();
    }
    else if (nChoice == 2) {
        float ambient[] = { 0.1745f, 0.01175f, 0.01175f, 0.55f };
        float diffuse[] = { 0.61424f, 0.04136f, 0.04136f, 0.55f };
        float specular[] = { 0.727811f, 0.626959f, 0.626959f, 0.55f };
        float shininess = 76.8f;
        setupMaterial(ambient, diffuse, specular, shininess);
        shape.DrawShape2();
    }
    else if (nChoice == 3) {shape.DrawShape3();
    }
    else if (nChoice == 4) {
        shape.DrawShape4();
    }
    else if (nChoice == 5) {
        float ambient[] = { 0.05f, 0.05f, 0.05f, 1.0f };
        float diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f};
        float specular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
        float shininess = 10.0f;
        setupMaterial(ambient, diffuse, specular, shininess);
        ;
    }
    glPopMatrix();
}

void Mesh::DrawMechanicDevice(bool drawFlag, int nChoice) {
    Mesh shape;
    shape.drawMeshFlag = drawFlag;
    if (nChoice == 1) {
        float ambient[] = { 0.105882f, 0.058824f, 0.113725f, 1.0f };
        float diffuse[] = { 0.427451f, 0.470588f, 0.541176f, 1.0f };
        float specular[] = { 0.333333f, 0.333333f, 0.521569f, 1.0f };
        float shininess = 9.84615f;
        setupMaterial(ambient, diffuse, specular, shininess);
        shape.DrawShape1();
    }
    else if (nChoice == 2) {
        float ambient[] = { 0.25f, 0.20725f, 0.20725f, 0.922f };
        float diffuse[] = { 1.0f, 0.829f, 0.829f, 0.922f };
        float specular[] = { 0.296648f, 0.296648f, 0.296648f, 0.922f };
        float shininess = 11.264f;
        setupMaterial(ambient, diffuse, specular, shininess);
        shape.DrawShape2();
    }
    else if (nChoice == 3) {
        float ambient[] = { 0.2295f, 0.08825f, 0.0275f, 1.0f };
        float diffuse[] = { 0.5508f, 0.2118f, 0.066f, 1.0f };
        float specular[] = { 0.580594f, 0.223257f, 0.0695701f, 1.0f };
        float shininess = 51.2f;
        setupMaterial(ambient, diffuse, specular, shininess);
        shape.DrawShape3();
    }
    else if (nChoice == 4) {
        float ambient[] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
        float diffuse[] = { 0.07568f, 0.61424f, 0.07568f, 0.55f };
        float specular[] = { 0.633f, 0.727811f, 0.633f, 0.55f };
        float shininess = 76.8f;
        setupMaterial(ambient, diffuse, specular, shininess);
        shape.DrawShape4();
    }
    else if (nChoice == 5) {
        float ambient[] = { 0.0f, 0.05f, 0.0f, 1.0f };
        float diffuse[] = { 0.4f, 0.5f, 0.4f, 1.0f };
        float specular[] = { 0.04f, 0.7f, 0.04f, 1.0f };
        float shininess = 10.0f;
        setupMaterial(ambient, diffuse, specular, shininess);
        shape.DrawShape5(15, 1, 1, 1);
        if (drawFlag) {
            shape.DrawWireframe();
        } else {
            shape.Draw();
        }
    }
}
