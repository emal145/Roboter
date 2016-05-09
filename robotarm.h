#ifndef ROBOTARM_H
#define ROBOTARM_H
#include "kugel.h"
#include "quader.h"
#include "rotationsmatrix.h"

class robotarm
{
public:
    robotarm();
    void drawRobot();
    void setRotationX(float rotx);
    void setRotationY(float roty);
    void setRotationZ(float rotz);

protected:
    kugel kug;
    quader quad;
    float rotx;
    float roty;
    float rotz;
    rotationsmatrix rotm;
};

#endif // ROBOTARM_H
