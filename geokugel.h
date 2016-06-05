#ifndef GEOKUGEL_H
#define GEOKUGEL_H
#include "rotationsmatrix.h"
#include "robot.h"

#include <QWidget>
#include <QOpenGLWidget>

class geokugel
{
public:
    geokugel();
    geokugel(float r, float g, float b);
    float* drawKugel(float radius, float x, float y, float z, int kreisHoehe, int kreisBreite);

private:
    float* drawQuad(float radius, float dx, float dy, float dz, float alpha, float beta);
    float red;
    float green;
    float blue;
    float dx;
    float dz;
    float dy;
    rotationsmatrix rotm;
};

#endif // GEOKUGEL_H
