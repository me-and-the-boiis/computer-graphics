#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"

class VertexID
{
public:
    int        vertIndex;
    int        colorIndex;
};

class Face
{
public:
    int         nVerts;
    VertexID*   vert;
    Vector3     facenorm;

    Face()
    {
        nVerts    = 0;
        vert    = NULL;
    }
    ~Face()
    {
        if(vert !=NULL)
        {
            delete[] vert;
            vert = NULL;
        }
        nVerts = 0;
    }
};

class Mesh
{
public:
    int        numVerts;
    Point3*        pt;

    int        numFaces;
    Face*        face;

    bool drawMeshFlag = 0;
public:
    Mesh()
    {
        numVerts    = 0;
        pt        = NULL;
        numFaces    = 0;
        face        = NULL;
        drawMeshFlag    = 0;
    }
    ~Mesh()
    {
        if (pt != NULL)
        {
            delete[] pt;
        }
        if(face != NULL)
        {
            delete[] face;
        }
        numVerts = 0;
        numFaces = 0;
    }
    void DrawWireframe();
    void DrawColor();
    void CalculateFacesNorm();
    void Draw();
    void BigDraw(float shape2Angle);
    void reflect(float shape2Angle);
    
    void BigDraw(float shape2Angle, float drawFlag);
    void specialDraw();

    void DrawMechanicDevice(bool drawFlag, int nChoice);

    void CreatePizza(int nSegment, float fAngle, float fHeight, float fRadius);
    void CreateJoint(int nSegment, float fWidth, float fLength, float fHeight);
    void CreatePismatic(float fHeight, float x, float x0 = -10, float z0 = -10, float x1 = -10, float z1 = -10);
    void CreateShape5(int nSegment, float fWidth, float fLength, float fHeight);
    void DrawCylinder();
    void DrawShape0();
    void DrawShape1();
    void DrawShape2();
    void DrawShape3();
    void DrawShape4();
    void DrawShape5();
};

void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness);
#endif
