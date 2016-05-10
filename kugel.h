#ifndef KUGEL_H
#define KUGEL_H

#include <QWidget>
#include <QOpenGLWidget>
#include "rotationsmatrix.h"

class kugel
{
public:
    kugel(float r = 1.0, float g = 0.0, float b = 0.0);
    void drawKugel(float radius, float x, float y, float z, int i, int j);
    void setRotationX(float radius, float rotx);
    void setRotationY(float radius,float roty);
    void setRotationZ(float radius,float rotz);

private:
    void drawQuad(float radius, float dx, float dy, float dz, float alpha, float beta);

    float red;
    float green;
    float blue;
    float rotx;
    float roty;
    float rotz;
    float dx;
    float dz;
    float dy;
    float  rotr;
    rotationsmatrix rotm;
};

#endif // KUGEL_H
