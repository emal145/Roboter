#ifndef GEOKEGEL_H
#define GEOKEGEL_H
#include <QWidget>
#include <QOpenGLWidget>
#include <math.h>

class geoKegel
{
public:
    geoKegel();
    geoKegel(float red, float green, float blue);
    float* drawKegel( float radius, float height, float heightCounter, float kegelBreite, float dx, float dy, float dz);

private:
    float* drawQuad(float radius, float hoehe, float alpha);
    void drawTriangle(float radius);

    float red;
    float green;
    float blue;
    float dx;
    float dy;
    float dz;

};

#endif // GEOKEGEL_H
