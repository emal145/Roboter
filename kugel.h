#ifndef KUGEL_H
#define KUGEL_H

#include <QWidget>
#include <QOpenGLWidget>
#include "rotationsmatrix.h";

class kugel
{
public:
    kugel(float r = 1.0, float g = 0.0, float b = 0.0);
    void drawKugel(float radius, float x, float y, float z, int i, int j);
    void drawKugel(float radius, float x, float y, float z, int i, int j, float rotx, float roty, float rotz);
    void setRotationX(float rotx);
    void setRotationY(float roty);
    void setRotationZ(float rotz);

private:
    void drawQuad(float radius, float dx, float dy, float dz, float alpha, float beta, float rotx, float roty, float rotz);

    float red;
    float green;
    float blue;
    float rotx;
    float roty;
    float rotz;
    rotationsmatrix rotm;
};

#endif // KUGEL_H
