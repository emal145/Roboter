#ifndef QUADER_H
#define QUADER_H
#include <QWidget>
#include <QOpenGLWidget>
#include "rotationsmatrix.h"

class quader
{
public:
    quader();
    quader(int armsPos);
    void drawCube(float red, float yellow, float blue, float s, float h, float dx, float dy, float dz, bool top);
    void rotateX(float radius, float rotx);
    void rotateY(float radius,float roty);
    void rotateZ(float radius,float rotz);
    void setRotationsZvalue(float* rotationZvalue, float* jointaddHeights);
   // void setJointAddHeightValue(int position, float height);

private:
    void initialize();
    void drawGroundorTop(float s, float h);
    void drawQuads(float s, float h);

    float red;
    float yellow;
    float blue;
    float s;
    float h;
    float dx;
    float dy;
    float dz;
    float *rotationsZ;
    float *jointaddHeight;
    int armsPos;

    bool top;
    float rotx;
    float roty;
    float rotz;
    float rotr;

protected:
    rotationsmatrix rotm;
    int counter;


};

#endif // QUADER_H
