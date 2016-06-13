#ifndef GEOZYLINDER_H
#define GEOZYLINDER_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>


class geozylinder
{
public:
    geozylinder();
    geozylinder(float red, float green, float blue);
    float* drawZylinder(float radius, float height, int counter, int breite, float dx, float dy, float dz);

private:
    void drawBoden(float radius, float dx, float dy, float dz);
    float* drawQuad(float radius, float height, float stepheight, int breite, float dx, float dy, float dz);

    float red;
    float green;
    float blue;
    float radius;
    float height;
    float dx;
    float dy;
    float dz;
};

#endif // GEOZYLINDER_H
