#ifndef ZYLINDER_H
#define ZYLINDER_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>


class zylinder
{
public:
    zylinder();
    zylinder(float red, float green, float blue);
    void drawZylinder(float radius, float height, float dx, float dy, float dz);


private:
    float red;
    float green;
    float blue;
    float radius;
    float height;
    float dx;
    float dy;
    float dz;
};

#endif // ZYLINDER_H
