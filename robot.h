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
    void calculatRotations();
private:
    robotarm *robotarms;
    zylinder robotBottom;
    float width;
    float height;
    int nRobotarms;
    float x;
    float y;
    float z;
    float* armsz;
    float robotBottomRotY;
};

#endif // ROBOT_H
