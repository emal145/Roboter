#ifndef GEOQUAD_H
#define GEOQUAD_H
#include "rotationsmatrix.h"
#include <QWidget>
#include <QOpenGLWidget>

class GeoQuad
{ 
public:
    GeoQuad();
    float* drawCube(float red, float yellow, float blue, float s, float h, float cubesheight, int cubesSideCounter, float dx, float dy, float dz, bool top);

private:
    void drawGroundorTop(float s, float h);
    float* drawQuads(float s, float h);

    float red;
    float yellow;
    float blue;
    float s;
    float h;
    float dx;
    float dy;
    float dz;
    bool top;
   int counter;
   rotationsmatrix rotm;

};

#endif // GEOQUAD_H
