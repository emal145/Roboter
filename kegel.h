#ifndef KEGEL_H
#define KEGEL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <math.h>

class Kegel
{
public:
    Kegel();
    Kegel(float red, float green, float blue, int amrsPos);
    float* drawKegel( float radius, float height, float heightCounter, float dx, float dy, float dz);
    void setRotationsZvalue(float* rotationZvalue, float* jointaddHeights);
    void rotateX(float rotx);
    void rotateY(float roty);
    void rotateZ(float rotz);

private:
    void drawQuad(float radius, float hoehe);
    void drawTriangle(float radius);

    float red;
    float green;
    float blue;
    float dx;
    float dy;
    float dz;
    float *rotationsZ;
    float *jointaddHeight;
    int armsPos;
    float rotx;
    float roty;
    float rotz;


};

#endif // KEGEL_H
