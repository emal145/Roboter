#ifndef ROBOTARM_H
#define ROBOTARM_H
#include "kugel.h"
#include "quader.h"
#include "rotationsmatrix.h"

class robotarm
{
public:
    robotarm();
    robotarm(float width, float height, float x, float y, float z);
    void drawRobot();
    void setWidth(float width);
    void setHeight(float height);
    void translateX(float x);
    void translateY(float y);
    void translateZ(float z);

    void rotateX(float rotx);
    void rotateY(float roty);
    void rotateZ(float rotz);

protected:
    kugel kug;
    quader quad;
    float rotx;
    float roty;
    float rotz;
    float width;
    float height;
    float x;
    float y;
    float z;
    rotationsmatrix rotm;
};

#endif // ROBOTARM_H
