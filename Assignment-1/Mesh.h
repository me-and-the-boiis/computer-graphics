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
public:
    Mesh()
    {
        numVerts    = 0;
        pt        = NULL;
        numFaces    = 0;
        face        = NULL;
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
    void BigDraw();

    void CreatePizza(int nSegment, float fAngle, float fHeight, float fRadius);
    void CreateJoint(int nSegment, float fWidth, float fLength, float fHeight);
    void CreatePismatic(float fHeight, float x, float x0 = -10, float z0 = -10, float x1 = -10, float z1 = -10);
    void DrawShape1();
    void DrawShape2();
    void DrawShape3();
    void DrawShape4();
    void DrawShape5(int nSegment, float fWidth, float fLength, float fHeight);
};

#endif
