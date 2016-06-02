#ifndef KUGEL_H
#define KUGEL_H

#include <QWidget>
#include <QOpenGLWidget>
#include "rotationsmatrix.h"

class kugel
{
public:
    kugel(float r = 1.0, float g = 0.0, float b = 0.0);
    kugel(float r, float g, float b, int armPos);
    void drawKugel(float radius, float x, float y, float z, int kreisHoehe, int kreisBreite);
    void setRotationX(float rotx);
    void setRotationY(float roty);
    void setRotationZ(float rotz);
    void setRotationsZvalue(float* rotationsZ, float* jointaddHeights);
    void initialize();

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
    float* rotationsZ;
    float* jointaddHeights;
    int armPos;
    rotationsmatrix rotm;
};

#endif // KUGEL_H
