#ifndef ROBOTARM_H
#define ROBOTARM_H
#include "kugel.h"
#include "quader.h"
#include "rotationsmatrix.h"
#include "kegel.h"

class robotarm
{
public:
    robotarm();
    ~robotarm();
    robotarm(float width, float height, float x, float y, float z, int robotPosition, bool endArm);

    void drawRobot();
    void setWidth(float width);
    void setHeight(float height);
    void translateX(float x);
    void translateY(float y);
    void translateZ(float z);

    void setChildArm(robotarm &childArm);
    void rotateZfromParent(int position, float rotz, float jointaddHeight);

    void rotateX(float rotx);
    void rotateY(float roty);
    void rotateZ(float rotz);


protected:
    kugel kug;
    quader quad;
    robotarm* childArm;
    Kegel keg;
    int robotPosition;
    float rotx;
    float roty;
    float rotz;
    float width;
    float height;
    float x;
    float y;
    float z;
    float radius;
    float *rotationsZ;
    float *jointaddHeights;
    float *jointaddHeightsKugel;
    bool endArm;


    rotationsmatrix rotm;
};

#endif // ROBOTARM_H
