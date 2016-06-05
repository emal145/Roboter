#ifndef ROBOT_H
#define ROBOT_H
#include "robotarm.h"
#include "zylinder.h"

class robot
{
public:
    robot();
    void drawRobot();
    void moveJoint(int position, float rotZ);
    void setArmZ(int pos, float z);
    void calculatRotations(float* endeffektor);
    void setEndeffektorx(float x);
    void setEndeffektory(float y);
    void setEndeffektorz(float z);
    float endeffektorx;
    float endeffektory;
    float endeffektorz;

private:
    robotarm *robotarms;
    zylinder robotBottom;
    float width;
    float* roboterHeights;
    int nRobotarms;
    float robotBottomHeight;
    float x;
    float y;
    float z;
    float* armsz;
    float robotBottomRotY;

};

#endif // ROBOT_H
