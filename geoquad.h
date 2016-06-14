#ifndef GEOQUAD_H
#define GEOQUAD_H
#include "rotationsmatrix.h"
#include <QWidget>
#include <QOpenGLWidget>

class GeoQuad
{ 
public:
    GeoQuad();
    float* drawCube(float red, float yellow, float blue, float s, float h, int qubescounter, int sideCounter, int sidePartCounter, float dx, float dy, float dz, bool top);

private:
    float* drawGroundorTop(float s, float h, int sidePartCounter);
    float* drawQuads(float s, float h, float stepheight,int sideCounter, int sidePartCounter);

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
