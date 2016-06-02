#ifndef ROBOT_H
#define ROBOT_H
#include "robotarm.h"

class robot
{
public:
    robot();
    void drawRobot();
    void moveJoint(int position, float rotZ);
   void setArmZ(int pos, float z);

private:
    robotarm *robotarms;
    float width;
    float height;
    int nRobotarms;
    float x;
    float y;
    float z;
    float* armsz;
};

#endif // ROBOT_H
